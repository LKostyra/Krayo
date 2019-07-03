@echo off

REM TODO:
REM  * Discover CPU count

call :path_check cmake.exe
call :path_check msbuild.exe

set script_path=%~dp0
set config=Release
set clean=0
set cmake_generator="Visual Studio 16 2019"
set cmake_architecture=""
set msbuild_platform=""
set msbuild_rtlib=""
set to_rebuild=

:argparse_loop
if NOT "%1" == "" (
    if "%1" == "Debug" (
        set config=Debug
        set msbuild_rtlib="d"
    ) else if "%1" == "Clean" (
        set clean=1
    ) else if "%1" == "x64" (
        set msbuild_platform=x64
        set cmake_architecture="x64"
    ) else if "%1" == "Win32" (
        set msbuild_platform=Win32
        set cmake_architecture="Win32"
    ) else if "%1" == "Rebuild" (
        set to_rebuild=%2
        shift /1
    )

    shift /1
    goto :argparse_loop
)

pushd .

cd "%script_path%"
echo Current directory is %cd%

REM ========== Krayo deps build ===========

REM Prepare build tree
call :setup_build_tree
if %ERRORLEVEL% GEQ 1 (
    if %ERRORLEVEL% EQU 1 (
        exit /b 0
    ) else (
        echo.
        echo Error while setting up build tree
        echo.
        exit /b %ERRORLEVEL%
    )
)

REM Check if FBX SDK is where it's supposed to be
echo | set /p=Checking for FBX SDK...
if NOT EXIST fbxsdk (
    echo NOT FOUND
    echo.
    echo FBX SDK was not found
    echo Make sure FBX SDK is either linked, or installed in "Deps/fbxsdk" directory.
    echo Symlinking/junctioning the directory to "fbxsdk" link over here also works,
    echo as long as installation's "include" and "lib" directories are visible inside.
    echo.
    exit /b 1
) else (
    if EXIST "fbxsdk\include\fbxsdk.h" (
        echo FOUND
    ) else (
        echo INVALID
        echo.
        echo FBX SDK installation linked under "fbxsdk" link/directory is missing FBX SDK header.
        echo.
        exit /b 1
    )
)

if NOT "%to_rebuild%" == "" (
    cd %to_rebuild%
    call :ms_build %to_rebuild% %to_rebuild% Rebuild
    if %ERRORLEVEL% GEQ 1 (
        echo.
        echo Failed to rebuild %to_rebuild%
        echo.
        exit /b %ERRORLEVEL%
    )

    popd .
    exit /b 0
)

REM lkCommon
cd lkCommon
call :ms_build lkCommon lkCommon
if %ERRORLEVEL% GEQ 1 (
    echo.
    echo Failed to build lkCommon
    echo.
    exit /b %ERRORLEVEL%
)
cd ..

REM Create solutions for dependencies
call :cmake_create
if %ERRORLEVEL% GEQ 1 (
    echo.
    echo Failed to create build files from CMake
    echo.
    exit /b %ERRORLEVEL%
)

cd %cmake_dir%

REM shaderc
cd shaderc\src

call :ms_build shaderc shaderc
if %ERRORLEVEL% GEQ 1 (
    echo.
    echo Failed to build shaderc
    echo.
    exit /b %ERRORLEVEL%
)

cd ..\..

cd "%script_path%"
copy /y nul "%build_done_file%"

echo.
echo Script is done
echo.

popd

exit /b 0



REM ========== Functions ==========

REM Checks if executable exists in PATH
REM   %1 - name of execuable to check
:path_check
echo | set /p=Checking for %1...
for %%X in (%1) do (set FOUND=%%~$PATH:X)
if defined FOUND (
    echo FOUND
) else (
    echo NOT FOUND
    echo     Make sure %1 is visible in PATH env variable before using this script.
    exit /b 1
)

exit /b 0



REM Sets up build tree for dependencies. Returns 1 if tree is already done
:setup_build_tree
echo | set /p=Setting up build tree...
set build_dir=%script_path%build
set bin_dir=%script_path%Bin
set cmake_dir=%build_dir%\%msbuild_platform%\%config%
set output_dir=%bin_dir%\%msbuild_platform%\%config%
set build_done_file=%output_dir%\.build_done

REM check if we're rebuilding something
if NOT "%to_rebuild%" == "" (
    echo REBUILDING %to_rebuild%
    exit /b 0
)

REM check if build tree already exists and exit early if it does
REM TODO add check for build artifacts
if EXIST "%build_done_file%" (
    echo ALREADY BUILT
    exit /b 1
)

REM clean leftover outputs to clean rebuild the deps
REM this also covers the situation where build was paused halfway-through, or failed

REM remove the build dir so it gets recreated later on
>nul 2>nul rmdir /s /q "%cmake_dir%"
>nul 2>nul dir /a-d /s "%build_dir%"
if %ERRORLEVEL% EQU 1 (
    REM FIXME this does not enter when run through VS
    rmdir /s /q "%build_dir%"
)
>nul 2>nul rmdir /s /q "%output_dir%"
>nul 2>nul dir /a-d /s "%bin_dir%"
if %ERRORLEVEL% EQU 1 (
    REM FIXME this does not enter when run through VS
    rmdir /s /q "%bin_dir%"
)

mkdir "%cmake_dir%"
mkdir "%output_dir%"
echo DONE

exit /b 0




REM Builds given project from solution using msbuild. Forces output to predefined output dir.
REM   %1 - Solution to select project from.
REM   %2 - Project to be built. Can be omitted - then assumes same project name as solution.
:ms_build
if NOT "%2"=="" (
    set project=%2
    set solution=%1.sln
) else (
    set project=%1
    set solution=%project%.sln
)

if "%3" == "Rebuild" (
    set project=%project%:Rebuild
)

msbuild %solution% /t:%project% /p:Configuration=%config%;Platform=%msbuild_platform% /p:OutDir="%output_dir%\\"
if %ERRORLEVEL% GEQ 1 (
    echo.
    echo Build failed
    echo.
    exit /b %ERRORLEVEL%
)

exit /b 0


REM Create build files from cmake
:cmake_create
cd %cmake_dir%

cmake ..\..\.. -DCMAKE_BUILD_TYPE=%config% -G %cmake_generator% -A %cmake_architecture%
if %ERRORLEVEL% GEQ 1 (
    echo.
    echo CMake generation failed
    echo.
    exit /b %ERRORLEVEL%
)

exit /b 0
