#pragma once

#include "Krayo/Engine.hpp"

#include "Renderer/HighLevel/Renderer.hpp"

#include "Events/EventManager.hpp"

#include <lkCommon/Math/RingAverage.hpp>


namespace Krayo {

class Engine::Impl
{
    lkCommon::Math::RingAverage<float, 300> mAvgTime;

    Renderer::Renderer mRenderer;
    Events::EventManager mEventManager;
    Scene::Scene mScene;
    Scene::Camera mCamera;

    // captures CWD, navigates to app root dir and verifies if it's correct
    bool SetDirTree() const;
    void Update();

public:
    Impl();
    ~Impl();

    bool Init(const EngineDesc& desc);
    void MainLoop();
    bool RegisterToEvent(const Events::ID id, Events::ISubscriber* subscriber);
    void EmitEvent(const Events::ID id, const Events::IMessage* message);
};

} // namespace Krayo
