SET(KRAYO_SRCS source/ResourceDir.cpp
               source/API/Component.cpp
               source/API/Engine.cpp
               source/API/EngineImpl.cpp
               source/API/Events.cpp
               source/API/Map.cpp
               source/API/Material.cpp
               source/API/Object.cpp
               source/API/Component/Light.cpp
               source/Events/EventManager.cpp
               source/Math/AABB.cpp
               source/Math/Frustum.cpp
               source/Math/Plane.cpp
               source/Renderer/LowLevel/Backbuffer.cpp
               source/Renderer/LowLevel/Buffer.cpp
               source/Renderer/LowLevel/CommandBuffer.cpp
               source/Renderer/LowLevel/Debugger.cpp
               source/Renderer/LowLevel/DescriptorAllocator.cpp
               source/Renderer/LowLevel/Device.cpp
               source/Renderer/LowLevel/Extensions.cpp
               source/Renderer/LowLevel/Framebuffer.cpp
               source/Renderer/LowLevel/Instance.cpp
               source/Renderer/LowLevel/MultiPipeline.cpp
               source/Renderer/LowLevel/Pipeline.cpp
               source/Renderer/LowLevel/QueueManager.cpp
               source/Renderer/LowLevel/RingBuffer.cpp
               source/Renderer/LowLevel/Shader.cpp
               source/Renderer/LowLevel/Texture.cpp
               source/Renderer/LowLevel/Tools.cpp
               source/Renderer/LowLevel/Translations.cpp
               source/Renderer/LowLevel/Util.cpp
               source/Renderer/LowLevel/VertexLayout.cpp
               source/Renderer/LowLevel/Linux/LinuxBackbuffer.cpp
               source/Renderer/HighLevel/DepthPrePass.cpp
               source/Renderer/HighLevel/ForwardPass.cpp
               source/Renderer/HighLevel/GridFrustumsGenerator.cpp
               source/Renderer/HighLevel/LightCuller.cpp
               source/Renderer/HighLevel/ParticleEngine.cpp
               source/Renderer/HighLevel/ParticlePass.cpp
               source/Renderer/HighLevel/Renderer.cpp
               source/Renderer/HighLevel/ResourceFactory.cpp
               source/Renderer/HighLevel/ShaderMacroDefinitions.cpp
               source/Scene/Camera.cpp
               source/Scene/Emitter.cpp
               source/Scene/Light.cpp
               source/Scene/Map.cpp
               source/Scene/Material.cpp
               source/Scene/Mesh.cpp
               source/Scene/Model.cpp
               source/Utils/FBXFile.cpp
               )

SET(KRAYO_HDRS source/Prerequisites.hpp
               source/ResourceDir.hpp
               source/API/EngineImpl.hpp
               source/Events/EventManager.hpp
               source/Math/AABB.hpp
               source/Math/Frustum.hpp
               source/Math/Plane.hpp
               source/Renderer/LowLevel/Backbuffer.hpp
               source/Renderer/LowLevel/Buffer.hpp
               source/Renderer/LowLevel/CommandBuffer.hpp
               source/Renderer/LowLevel/Debugger.hpp
               source/Renderer/LowLevel/DescriptorAllocator.hpp
               source/Renderer/LowLevel/Device.hpp
               source/Renderer/LowLevel/Extensions.hpp
               source/Renderer/LowLevel/Framebuffer.hpp
               source/Renderer/LowLevel/Instance.hpp
               source/Renderer/LowLevel/MultiPipeline.hpp
               source/Renderer/LowLevel/Pipeline.hpp
               source/Renderer/LowLevel/QueueManager.hpp
               source/Renderer/LowLevel/RingBuffer.hpp
               source/Renderer/LowLevel/Shader.hpp
               source/Renderer/LowLevel/Texture.hpp
               source/Renderer/LowLevel/Tools.hpp
               source/Renderer/LowLevel/Translations.hpp
               source/Renderer/LowLevel/Types.hpp
               source/Renderer/LowLevel/Util.hpp
               source/Renderer/LowLevel/VertexLayout.hpp
               source/Renderer/LowLevel/VkRAII.hpp
               source/Renderer/LowLevel/Linux/LinuxBackbuffer.hpp
               source/Renderer/HighLevel/DepthPrePass.hpp
               source/Renderer/HighLevel/ForwardPass.hpp
               source/Renderer/HighLevel/GridFrustumsGenerator.hpp
               source/Renderer/HighLevel/LightCuller.hpp
               source/Renderer/HighLevel/ParticleEngine.hpp
               source/Renderer/HighLevel/ParticlePass.hpp
               source/Renderer/HighLevel/Renderer.hpp
               source/Renderer/HighLevel/ResourceFactory.hpp
               source/Renderer/HighLevel/ShaderMacroDefinitions.hpp
               source/Scene/Camera.hpp
               source/Scene/Emitter.hpp
               source/Scene/Light.hpp
               source/Scene/Map.hpp
               source/Scene/Material.hpp
               source/Scene/Mesh.hpp
               source/Scene/Model.hpp
               source/Utils/FBXFile.hpp
               source/Utils/Traits.hpp
               )

SET(KRAYO_API_HDRS include/Krayo/ApiDef.hpp
                   include/Krayo/ApiPrerequisites.hpp
                   include/Krayo/Component.hpp
                   include/Krayo/Engine.hpp
                   include/Krayo/Events.hpp
                   include/Krayo/Map.hpp
                   include/Krayo/Material.hpp
                   include/Krayo/Object.hpp
                   include/Krayo/Component/Light.hpp
                   )

ADD_LIBRARY(${KRAYO_TARGET} SHARED
            ${KRAYO_SRCS} ${KRAYO_HDRS} ${KRAYO_API_HDRS}
            )

ADD_DEPENDENCIES(${KRAYO_TARGET} lkCommon shaderc)

TARGET_INCLUDE_DIRECTORIES(${KRAYO_TARGET}
                           PRIVATE ${KRAYO_ROOT_DIRECTORY}/Deps/lkCommon/lkCommon/include
                           PRIVATE ${KRAYO_ROOT_DIRECTORY}/Deps/fbxsdk/include
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source
                           )

TARGET_COMPILE_DEFINITIONS(${KRAYO_TARGET}
                           PRIVATE "-DKRAYO_ROOT_REL_TO_BIN=\"../..\""
                           PRIVATE "-DKRAYO_ROOT_DIR=R\"(${KRAYO_ROOT_DIRECTORY}/)\""
                           PRIVATE "-DKRAYO_EXPORTS"
                           PRIVATE "-DVK_USE_PLATFORM_XCB_KHR"
                           PRIVATE "-DVK_NO_PROTOTYPES"
                           )

TARGET_COMPILE_OPTIONS(${KRAYO_TARGET}
                       PRIVATE "-std=c++1y"
                       PRIVATE "-msse4.1"
                       PRIVATE "-fvisibility=hidden"
                       PRIVATE "-fPIC"
                       )

TARGET_LINK_LIBRARIES(${KRAYO_TARGET} lkCommon dl libfbxsdk.a shaderc ${KRAYO_PKG_DEPS_LIBRARIES})

KRAYO_COPY_RESULT(${KRAYO_TARGET})
