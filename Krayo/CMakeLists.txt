SET(KRAYO_SRCS source/ResourceDir.cpp
               source/API/Engine.cpp
               source/API/EngineImpl.cpp
               source/API/Events.cpp
               source/API/Resource/Manager.cpp
               source/API/Resource/Model.cpp
               source/API/Scene/Map.cpp
               source/API/Scene/Object.cpp
               source/Component/Emitter.cpp
               source/Component/Light.cpp
               source/Component/IComponent.cpp
               source/Component/Mesh.cpp
               source/Component/Model.cpp
               source/Events/Manager.cpp
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
               source/Resource/IResource.cpp
               source/Resource/Manager.cpp
               source/Resource/Material.cpp
               source/Resource/Model.cpp
               source/Resource/Texture.cpp
               source/Scene/Camera.cpp
               source/Scene/Map.cpp
               source/Scene/Object.cpp
               source/Utils/ModelLoader.cpp
               source/Utils/ModelFiles/FBXModelFile.cpp
               )

SET(KRAYO_HDRS source/Prerequisites.hpp
               source/ResourceDir.hpp
               source/API/EngineImpl.hpp
               source/Component/Emitter.hpp
               source/Component/IComponent.hpp
               source/Component/Light.hpp
               source/Component/Mesh.hpp
               source/Component/Model.hpp
               source/Events/Manager.hpp
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
               source/Resource/IResource.hpp
               source/Resource/Manager.hpp
               source/Resource/Material.hpp
               source/Resource/Model.hpp
               source/Resource/Texture.hpp
               source/Scene/Camera.hpp
               source/Scene/Map.hpp
               source/Scene/Object.hpp
               source/Utils/ModelFile.hpp
               source/Utils/ModelLoader.hpp
               source/Utils/Traits.hpp
               source/Utils/ModelFiles/FBXModelFile.hpp
               )

SET(KRAYO_API_HDRS include/Krayo/ApiDef.hpp
                   include/Krayo/ApiPrerequisites.hpp
                   include/Krayo/Engine.hpp
                   include/Krayo/Events.hpp
                   include/Krayo/Resource/Model.hpp
                   include/Krayo/Resource/Manager.hpp
                   include/Krayo/Scene/Map.hpp
                   include/Krayo/Scene/Object.hpp
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
