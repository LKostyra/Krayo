PKG_CHECK_MODULES(KRAYOGAME_PKG_DEPS REQUIRED
                  xcb xcb-image libxml-2.0
                  )

SET(KRAYOGAME_SRCS Main.cpp
                   )

ADD_EXECUTABLE(${KRAYOGAME_TARGET}
               ${KRAYOGAME_SRCS} ${KRAYOGAME_HDRS}
               )

ADD_DEPENDENCIES(${KRAYOGAME_TARGET} lkCommon)

TARGET_INCLUDE_DIRECTORIES(${KRAYOGAME_TARGET}
                           PRIVATE ${KRAYOGAME_ROOT_DIRECTORY}/Deps/lkCommon/lkCommon/include
                           PRIVATE ${KRAYOGAME_ROOT_DIRECTORY}/Deps/rapidjson/include
                           PRIVATE ${KRAYOGAME_ROOT_DIRECTORY}/Deps/tinyobjloader
                           PRIVATE ${KRAYOGAME_ROOT_DIRECTORY}/Krayo/include/
                           )


TARGET_COMPILE_DEFINITIONS(${KRAYOGAME_TARGET}
                           PRIVATE "-DKRAYOGAME_ROOT_REL_TO_BIN=\"../..\""
                           PRIVATE "-DKRAYOGAME_ROOT_DIR=R\"(${KRAYOGAME_ROOT_DIRECTORY}/)\""
                           )

TARGET_COMPILE_OPTIONS(${KRAYOGAME_TARGET}
                       PRIVATE "-std=c++1y"
                       PRIVATE "-msse4.1"
                       )

TARGET_LINK_LIBRARIES(${KRAYOGAME_TARGET} Krayo lkCommon ${KRAYOGAME_PKG_DEPS_LIBRARIES})

KRAYO_COPY_RESULT(${KRAYOGAME_TARGET})
