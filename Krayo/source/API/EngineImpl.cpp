#include "API/EngineImpl.hpp"

#include "ResourceDir.hpp"

#include <lkCommon/System/FS.hpp>
#include <lkCommon/Utils/Logger.hpp>
#include <lkCommon/Utils/Timer.hpp>
#include <lkCommon/Math/RingAverage.hpp>
#include <lkCommon/Math/Constants.hpp>


namespace Krayo {

Engine::Impl::Impl()
    : mRenderer()
    , mScene()
    , mCamera()
{
}

Engine::Impl::~Impl()
{
    mRenderer.WaitForAll();
    LOGI("Engine destroyed");
}

bool Engine::Impl::SetDirTree() const
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

bool Engine::Impl::Init(const EngineDesc& desc)
{
    #ifdef KRAYO_ROOT_DIR
    lkCommon::Utils::Logger::SetRootPathToStrip(std::string(KRAYO_ROOT_DIR));
    #endif

    if (!SetDirTree())
    {
        LOGE("Failed to set directory tree to project root");
        return false;
    }

    if (!mWindow.Init())
    {
        LOGE("Failed to initialize Window");
        return false;
    }

    if (!mWindow.Open(200, 200, desc.windowWidth, desc.windowHeight, "Krayo"))
    {
        LOGE("Failed to open Window");
        return false;
    }

    Renderer::RendererDesc rendDesc;
    rendDesc.debugEnable = desc.debug;
    rendDesc.debugVerbose = desc.debugVerbose;
    rendDesc.window = &mWindow;
    rendDesc.vsync = desc.vsync;
    rendDesc.noAsync = true;
    rendDesc.nearZ = 0.2f;
    rendDesc.farZ = 500.0f;
    rendDesc.fov = LKCOMMON_DEG_TO_RADF(70.0f);
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

    Scene::MaterialDesc matDesc;
    matDesc.color = lkCommon::Utils::PixelFloat4(0.2f, 0.5f, 0.8f, 1.0f);

    Scene::Material* mat = mScene.GetMaterial("mat0").first;
    if (!mat->Init(matDesc))
        return false;

    Scene::ModelDesc modelDesc;
    modelDesc.materials.emplace_back(mat);

    Scene::Model* m = dynamic_cast<Scene::Model*>(mScene.GetComponent(Scene::ComponentType::Model, "obj0").first);
    if (!m->Init(modelDesc)) return false;
    m->SetPosition(0.0f, 0.0f, 0.0f);

    Scene::Object* o = mScene.CreateObject();
    o->SetComponent(m);

    auto lightResult = mScene.GetComponent(Scene::ComponentType::Light, "light0");
    Scene::Light* light = dynamic_cast<Krayo::Scene::Light*>(lightResult.first);
    light->SetDiffuseIntensity(1.0f, 1.0f, 1.0f);
    light->SetPosition(3.0f, 5.0f, 0.0f);

    Krayo::Scene::Object* lightObj = mScene.CreateObject();
    lightObj->SetComponent(light);

    Scene::CameraDesc camDesc;
    camDesc.pos = lkCommon::Math::Vector4(2.0f, 1.0f,-5.0f, 1.0f);
    camDesc.at = lkCommon::Math::Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    camDesc.up = lkCommon::Math::Vector4(0.0f,-1.0f, 0.0f, 0.0f);
    mCamera.Update(camDesc);

    return true;
}

void Engine::Impl::MainLoop()
{
    lkCommon::Utils::Timer timer;
    lkCommon::Math::RingAverage<float, 30> avgTime;
    timer.Start();

    while (mWindow.IsOpened())
    {
        float frameTime = static_cast<float>(timer.Stop());
        timer.Start();
        avgTime.Add(frameTime);
        float time = avgTime.Get();
        float fps = 1.0f / time;

        mWindow.SetTitle("Krayo - " + std::to_string(fps) + " FPS (" + std::to_string(time * 1000.0f) + " ms)");
        mWindow.Update(frameTime);
        mRenderer.Draw(mScene, mCamera, frameTime);
    }
}

bool Engine::Impl::RegisterToEvent(const EventID id, IEventSubscriber* subscriber)
{
    return mEventManager.RegisterToEvent(id, subscriber);
}

void Engine::Impl::EmitEvent(IEventMessage* message)
{
    mEventManager.EmitEvent(message);
}

} // namespace Krayo
