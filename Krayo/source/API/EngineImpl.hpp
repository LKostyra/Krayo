#pragma once

#include "Krayo/Engine.hpp"

#include "Renderer/HighLevel/Renderer.hpp"

#include "Events/EventManager.hpp"
#include "Scene/Map.hpp"

#include <lkCommon/Math/RingAverage.hpp>


namespace Krayo {

class Engine::Impl
{
    lkCommon::Math::RingAverage<float, 300> mAvgTime;

    Renderer::Renderer mRenderer;
    Events::EventManager mEventManager;

    std::vector<Krayo::Material> mMaterials;
    std::vector<Krayo::Map> mMaps;
    Krayo::Map* mCurrentMap;
    Scene::Camera mCamera;

    // captures CWD, navigates to app root dir and verifies if it's correct
    bool SetDirTree() const;
    void Update();
    Krayo::Map* CreateDefaultMap();

public:
    Impl();
    ~Impl();

    bool Init(const EngineDesc& desc);
    void MainLoop();

    Krayo::Map* CreateMap(const std::string& name);
    Krayo::Material* CreateMaterial(const std::string& name);

    void SetCurrentMap(Krayo::Map* map);
    Krayo::Map* GetCurrentMap();

    bool RegisterToEvent(const Events::ID id, Events::ISubscriber* subscriber);
    void EmitEvent(const Events::ID id, const Events::IMessage* message);
};

} // namespace Krayo
