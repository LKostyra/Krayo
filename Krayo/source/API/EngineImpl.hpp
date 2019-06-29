#pragma once

#include "Krayo/Engine.hpp"

#include "Renderer/HighLevel/Renderer.hpp"

#include "Events/EventManager.hpp"


namespace Krayo {

class Engine::Impl
{
    lkCommon::System::Window mWindow;
    Renderer::Renderer mRenderer;
    Events::EventManager mEventManager;
    Scene::Scene mScene;
    Scene::Camera mCamera;

    // captures CWD, navigates to app root dir and verifies if it's correct
    bool SetDirTree() const;

public:
    Impl();
    ~Impl();

    bool Init(const EngineDesc& desc);
    void MainLoop();
    bool RegisterToEvent(EventID id, IEventSubscriber* subscriber);
    void EmitEvent(IEventMessage* message);
};

} // namespace Krayo
