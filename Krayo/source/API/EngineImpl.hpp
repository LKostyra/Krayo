#pragma once

#include "Krayo/Engine.hpp"

#include "Events/Manager.hpp"
#include "Resource/Manager.hpp"

#include <lkCommon/Math/RingAverage.hpp>

#include <string>
#include <memory>
#include <unordered_map>


namespace Krayo {

class Engine::Impl
{
    lkCommon::Math::RingAverage<float, 300> mAvgTime;

    Events::Manager mEventManager;
    Resource::Internal::Manager mResourceManager;
    Resource::Manager mResourceManagerAPI;

    // captures CWD, navigates to app root dir and verifies if it's correct
    bool SetDirTree() const;
    void Update();

public:
    Impl();
    ~Impl();

    bool Init(const EngineDesc& desc);
    void MainLoop();

    std::shared_ptr<Scene::Internal::Map> CreateMap(const std::string& name);
    std::shared_ptr<Scene::Internal::Map> GetMap(const std::string& name);
    void SetCurrentMap(const std::shared_ptr<Scene::Internal::Map>& name);

    Resource::Manager& GetResourceManager();

    bool RegisterToEvent(const Events::ID id, Events::ISubscriber* subscriber);
    void EmitEvent(const Events::ID id, const Events::IMessage* message);
};

} // namespace Krayo
