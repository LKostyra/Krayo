#include "API/EngineImpl.hpp"

#include "ResourceDir.hpp"

#include <lkCommon/System/FS.hpp>
#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {

Engine::Impl::Impl()
    : mRenderer()
    , mScene()
    , mCamera()
{
    LOGI("Engine implementation created");
}

Engine::Impl::~Impl()
{
    mRenderer.WaitForAll();
    LOGI("Engine implementation destroyed");
}

bool Engine::Impl::Init(const EngineDesc& desc)
{
    if (desc.window == nullptr)
    {
        LOGE("Window is required to initialize Engine!");
        return false;
    }

    #ifdef KRAYO_ROOT_DIR
    lkCommon::Utils::Logger::SetRootPathToStrip(std::string(KRAYO_ROOT_DIR));
    #endif

    if (!lkCommon::System::FS::Exists(ResourceDir::SHADER_CACHE))
        lkCommon::System::FS::CreateDir(ResourceDir::SHADER_CACHE);

    Renderer::RendererDesc rendDesc;
    rendDesc.debugEnable = desc.debug;
    rendDesc.window = desc.window;
    rendDesc.noAsync = true;
    rendDesc.nearZ = 0.1f;
    rendDesc.farZ = 1000.0f;
    rendDesc.fov = 60.0f;
    if (!mRenderer.Init(rendDesc))
    {
        LOGE("Failed to initialize Engine's Renderer");
        return false;
    }

    if (!mScene.Init())
    {
        LOGE("Failed to create empty scene");
        return false;
    }

    Scene::CameraDesc camDesc;
    camDesc.pos = lkCommon::Math::Vector4(1.0f, 0.0f, 0.0f, 1.0f);
    camDesc.at = lkCommon::Math::Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    camDesc.up = lkCommon::Math::Vector4(0.0f, 1.0f, 0.0f, 0.0f);
    mCamera.Update(camDesc);

    return true;
}

void Engine::Impl::Draw(const float frameTime)
{
    mRenderer.Draw(mScene, mCamera, frameTime);
}

} // namespace Krayo
