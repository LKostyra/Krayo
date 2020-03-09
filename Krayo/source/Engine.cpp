#include "Engine.hpp"

#include "Resource/Manager.hpp"
#include "ResourceDir.hpp"

#include <lkCommon/System/FS.hpp>
#include <lkCommon/System/Window.hpp>
#include <lkCommon/Utils/Logger.hpp>
#include <lkCommon/Utils/Timer.hpp>
#include <lkCommon/Math/Constants.hpp>
#include <lkCommon/Math/Utilities.hpp>
#include <lkCommon/Math/RingAverage.hpp>


namespace Krayo {
namespace Internal {


class Window: public lkCommon::System::Window
{
    Events::Manager& mEventManager;
    float mAngleX, mAngleY;

protected:
    void OnUpdate(float deltaTime) override
    {
        /*const lkCommon::Math::Vector4 cameraFrontDir = (mCameraDesc.at - mCameraDesc.pos).Normalize();
        const lkCommon::Math::Vector4 cameraRightDir = cameraFrontDir.Cross(mCameraDesc.up).Normalize();
        const lkCommon::Math::Vector4 cameraUpDir = cameraRightDir.Cross(cameraFrontDir);

        lkCommon::Math::Vector4 newPos;
        if (IsKeyPressed(lkCommon::System::KeyCode::W)) newPos += cameraFrontDir;
        if (IsKeyPressed(lkCommon::System::KeyCode::S)) newPos -= cameraFrontDir;
        if (IsKeyPressed(lkCommon::System::KeyCode::D)) newPos += cameraRightDir;
        if (IsKeyPressed(lkCommon::System::KeyCode::A)) newPos -= cameraRightDir;
        if (IsKeyPressed(lkCommon::System::KeyCode::R)) newPos -= cameraUpDir;
        if (IsKeyPressed(lkCommon::System::KeyCode::F)) newPos += cameraUpDir;

        float speed = 2.0f * deltaTime;
        newPos *= speed;

        // new direction
        lkCommon::Math::Vector4 updateDir = lkCommon::Math::Matrix4::CreateRotationX(mAngleY) * lkCommon::Math::Vector4(0.0f, 0.0f, 1.0f, 0.0f);
        updateDir = lkCommon::Math::Matrix4::CreateRotationY(mAngleX) * updateDir;
        updateDir.Normalize();

        mCameraDesc.pos += newPos;
        mCameraDesc.at = mCameraDesc.pos + updateDir;
        mCamera.Update(mCameraDesc);*/
    }

    void OnKeyDown(const lkCommon::System::KeyCode key) override
    {
        Events::KeyDownMessage msg(static_cast<int>(key));
        mEventManager.EmitEvent(Events::ID::KeyDown, &msg);
    }

    void OnKeyUp(const lkCommon::System::KeyCode key) override
    {
        mEventManager.EmitEvent(Events::ID::KeyUp, new Events::KeyUpMessage(static_cast<int>(key)));
    }

    void OnMouseDown(const uint32_t button) override
    {
        mEventManager.EmitEvent(Events::ID::MouseDown, new Events::MouseDownMessage(button));
    }

    void OnMouseUp(const uint32_t button) override
    {
        mEventManager.EmitEvent(Events::ID::MouseUp, new Events::MouseUpMessage(button));
    }

    void OnMouseMove(const uint32_t x, const uint32_t y, const int32_t deltaX, const int32_t deltaY)
    {
        Events::MouseMoveMessage msg(x, y, deltaX, deltaY);
        mEventManager.EmitEvent(Events::ID::MouseMove, &msg);

        if (IsMouseKeyPressed(0))
        {
            mAngleX += deltaX * 0.005f;
            mAngleY += deltaY * 0.005f;
        }
    }

public:
    Window(Events::Manager& manager/*, Scene::Internal::Camera& camera*/)
        : mEventManager(manager)
        /*, mCamera(camera)
        , mCameraDesc()*/
        , mAngleX(0.0f)
        , mAngleY(0.0f)
    {
        /*mCameraDesc.pos = lkCommon::Math::Vector4(2.0f, 1.0f,-5.0f, 1.0f);
        mCameraDesc.at = lkCommon::Math::Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        mCameraDesc.up = lkCommon::Math::Vector4(0.0f,-1.0f, 0.0f, 0.0f);*/
    }
};

namespace {

// TEMPORARY
std::unique_ptr<Window> gWindow;

const float TICK_TIME = 0.01f; // 10ms update loop
const float TICK_TIME_INV = 1.0f / TICK_TIME;
const uint32_t MAX_FRAMESKIP = 5;

} // namespace


Engine::Engine()
    : mEventManager()
    , mResourceManager()
    , mResourceManagerAPI(mResourceManager)
    , mMaps()
    , mCurrentMap(nullptr)
{
}

Engine::~Engine()
{
    mRenderer.WaitForAll();
    LOGI("Engine destroyed");
}

bool Engine::SetDirTree() const
{
    std::string cwd = lkCommon::System::FS::GetParentDir(lkCommon::System::FS::GetExecutablePath());

    if (!lkCommon::System::FS::SetCWD(
            lkCommon::System::FS::JoinPaths(cwd, std::string(KRAYO_ROOT_REL_TO_BIN))
        ))
    {
        LOGE("Failed to set CWD to project's root");
        return false;
    }

    // TODO check if required resources (ex. shaders) exist

    if (!lkCommon::System::FS::Exists(ResourceDir::SHADER_CACHE))
    {
        if (!lkCommon::System::FS::CreateDir(ResourceDir::SHADER_CACHE))
        {
            LOGE("Failed to create directory for Shader Cache");
            return false;
        }
    }

    return true;
}

void Engine::Update()
{
    gWindow->Update(static_cast<float>(TICK_TIME));
}

bool Engine::Init(const EngineDesc& desc)
{
    #ifdef KRAYO_ROOT_DIR
    lkCommon::Utils::Logger::SetRootPathToStrip(std::string(KRAYO_ROOT_DIR));
    #endif

    if (!SetDirTree())
    {
        LOGE("Failed to set directory tree to project root");
        return false;
    }

    mEventManager.Init();

    gWindow = std::make_unique<Window>(mEventManager);
    if (!gWindow->Init())
    {
        LOGE("Failed to initialize Window");
        return false;
    }

    if (!gWindow->Open(200, 200, desc.windowWidth, desc.windowHeight, "Krayo"))
    {
        LOGE("Failed to open Window");
        return false;
    }

    Renderer::RendererDesc rendDesc;
    LKCOMMON_ZERO_MEMORY(rendDesc);
    rendDesc.debugEnable = desc.debug;
    rendDesc.debugVerbose = desc.debugVerbose;
    rendDesc.vsync = desc.vsync;
    rendDesc.noAsync = false;
    rendDesc.window = gWindow.get();
    rendDesc.fov = 60.0f;
    rendDesc.nearZ = 0.1f;
    rendDesc.farZ = 1000.0f;
    if (!mRenderer.Init(rendDesc))
    {
        LOGE("Failed to initialize Renderer");
        return false;
    }

    LOGI("Engine initialized successfully");
    return true;
}

void Engine::MainLoop()
{
    lkCommon::Math::RingAverage<float, 50> frameAvg;

    lkCommon::Utils::Timer timer;
    lkCommon::Utils::Timer updateTimer;
    timer.Start();
    updateTimer.Start();

    while (gWindow->IsOpened())
    {
        float frameTime = static_cast<float>(timer.Stop());
        timer.Start();
        frameAvg.Add(frameTime);
        gWindow->SetTitle("Krayo - Frame time " + std::to_string(frameAvg.Get() * 1000.0f) + " ms");

        uint32_t updateLoop = 0;
        float updateTime = static_cast<float>(updateTimer.Stop());
        while (updateTime > TICK_TIME && updateLoop < MAX_FRAMESKIP)
        {
            updateTime -= TICK_TIME;
            updateLoop++;

            if (updateTime < TICK_TIME)
            {
                updateTimer.Start(updateTime);
            }

            Update();

            // notify about update frameskip if it happens
            if (updateLoop >= MAX_FRAMESKIP && updateTime > TICK_TIME)
            {
                LOGW("Skipping " << static_cast<int>(updateTime * TICK_TIME_INV) << " update frames, updateTime " << updateTime);
                updateTimer.Start();
            }
        }

        float interpolation = updateTime * TICK_TIME_INV;
        if (interpolation > 1.0f)
            interpolation = 1.0f;

        if (mCurrentMap)
        {
            mRenderer.Draw(*mCurrentMap, updateTime, interpolation);
        }
    }
}

std::shared_ptr<Internal::Map>& Engine::CreateMap(const std::string& name)
{
    mMaps.emplace_back(new Internal::Map(name));
    return mMaps.back();
}

void Engine::SetCurrentMap(std::shared_ptr<Internal::Map>& map)
{
    mCurrentMap = map;
    LOGD("Set map " << reinterpret_cast<void*>(mCurrentMap.get()));
}

Krayo::Resource::Manager& Engine::GetResourceManager()
{
    return mResourceManagerAPI;
}

bool Engine::RegisterToEvent(const Events::ID id, Events::ISubscriber* subscriber)
{
    return mEventManager.RegisterToEvent(id, subscriber);
}

void Engine::EmitEvent(const Events::ID id, const Events::IMessage* message)
{
    mEventManager.EmitEvent(id, message);
}

} // namespace Internal
} // namespace Krayo
