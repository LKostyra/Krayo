#include "API/EngineImpl.hpp"

#include "ResourceDir.hpp"

#include <lkCommon/System/FS.hpp>
#include <lkCommon/Utils/Logger.hpp>
#include <lkCommon/Utils/Timer.hpp>
#include <lkCommon/Math/Constants.hpp>
#include <lkCommon/Math/Utilities.hpp>


namespace Krayo {


class Window: public lkCommon::System::Window
{
    Events::Manager& mEventManager;
    Scene::Camera& mCamera;
    Scene::CameraDesc mCameraDesc;
    float mAngleX, mAngleY;

protected:
    void OnUpdate(float deltaTime) override
    {
        const lkCommon::Math::Vector4 cameraFrontDir = (mCameraDesc.at - mCameraDesc.pos).Normalize();
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
        mCamera.Update(mCameraDesc);
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
    Window(Events::Manager& manager, Scene::Camera& camera)
        : mEventManager(manager)
        , mCamera(camera)
        , mCameraDesc()
        , mAngleX(0.0f)
        , mAngleY(0.0f)
    {
        mCameraDesc.pos = lkCommon::Math::Vector4(2.0f, 1.0f,-5.0f, 1.0f);
        mCameraDesc.at = lkCommon::Math::Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        mCameraDesc.up = lkCommon::Math::Vector4(0.0f,-1.0f, 0.0f, 0.0f);
    }
};

namespace {

// TEMPORARY
std::unique_ptr<Window> gWindow;

const float TICK_TIME = 0.01f; // 10ms update loop
const float TICK_TIME_INV = 1.0f / TICK_TIME;
const uint32_t MAX_FRAMESKIP = 5;

} // namespace


Engine::Impl::Impl()
    : mRenderer()
    , mEventManager()
    , mMaps()
    , mCurrentMap(nullptr)
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

void Engine::Impl::Update()
{
    gWindow->Update(static_cast<float>(TICK_TIME));
}

Krayo::Map* Engine::Impl::CreateDefaultMap()
{
    Krayo::Map* defaultMap = CreateMap("DEFAULT");

    Scene::Model* m = dynamic_cast<Scene::Model*>(defaultMap->CreateComponent(ComponentType::Model, "obj0"));
    if (!m->Init())
    {
        LOGE("Failed to init cube");
        return nullptr;
    }
    m->SetPosition(0.0f, 0.0f, 0.0f);

    Krayo::Object* o = defaultMap->CreateObject("object0");
    o->SetComponent(m);

    Krayo::Component* lightResult = defaultMap->CreateComponent(ComponentType::Light, "light0");
    Scene::Light* light = dynamic_cast<Krayo::Scene::Light*>(lightResult);
    light->SetDiffuseIntensity(1.0f, 1.0f, 1.0f);
    light->SetPosition(3.0f, 5.0f, 0.0f);

    Krayo::Object* lightObj = defaultMap->CreateObject("light0");
    lightObj->SetComponent(light);

    return defaultMap;
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

    mEventManager.Init();

    gWindow = std::make_unique<Window>(mEventManager, mCamera);
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
    rendDesc.debugEnable = desc.debug;
    rendDesc.debugVerbose = desc.debugVerbose;
    rendDesc.window = gWindow.get();
    rendDesc.vsync = desc.vsync;
    rendDesc.noAsync = true;
    rendDesc.nearZ = 0.1f;
    rendDesc.farZ = 500.0f;
    rendDesc.fov = LKCOMMON_DEG_TO_RADF(60.0f);
    if (!mRenderer.Init(rendDesc))
    {
        LOGE("Failed to initialize Engine's Renderer");
        return false;
    }

    mCurrentMap = CreateDefaultMap();
    if (!mCurrentMap)
    {
        LOGE("Failed to initialize Engine's default map");
        return false;
    }

    Scene::CameraDesc camDesc;
    camDesc.pos = lkCommon::Math::Vector4(2.0f, 1.0f,-5.0f, 1.0f);
    camDesc.at = lkCommon::Math::Vector4(2.0f, 1.0f, 0.0f, 1.0f);
    camDesc.up = lkCommon::Math::Vector4(0.0f,-1.0f, 0.0f, 0.0f);
    mCamera.Update(camDesc);

    return true;
}

void Engine::Impl::MainLoop()
{
    lkCommon::Utils::Timer timer;
    lkCommon::Utils::Timer updateTimer;
    timer.Start();
    updateTimer.Start();

    while (gWindow->IsOpened())
    {
        float frameTime = static_cast<float>(timer.Stop());
        timer.Start();

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

        mRenderer.Draw(*mCurrentMap->mImpl, mCamera, frameTime, interpolation);
    }
}

Krayo::Map* Engine::Impl::CreateMap(const std::string& name)
{
    mMaps.emplace_back(name);
    return &mMaps.back();
}

Krayo::Material* Engine::Impl::CreateMaterial(const std::string& name)
{
    mResourceManager.CreateResource(Resources::ResourceType::Material, name);
    return nullptr;
}

void Engine::Impl::SetCurrentMap(Krayo::Map* map)
{
    if (map == nullptr)
        mCurrentMap = &(*mMaps.begin());
    else
        mCurrentMap = map;
}

Krayo::Map* Engine::Impl::GetCurrentMap()
{
    return mCurrentMap;
}

bool Engine::Impl::RegisterToEvent(const Events::ID id, Events::ISubscriber* subscriber)
{
    return mEventManager.RegisterToEvent(id, subscriber);
}

void Engine::Impl::EmitEvent(const Events::ID id, const Events::IMessage* message)
{
    mEventManager.EmitEvent(id, message);
}

} // namespace Krayo
