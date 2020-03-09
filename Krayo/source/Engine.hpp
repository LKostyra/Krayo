#pragma once

#include "Krayo/Engine.hpp"

#include "Map.hpp"
#include "Events/Manager.hpp"
#include "Resource/Manager.hpp"
#include "Renderer/HighLevel/Renderer.hpp"

#include <lkCommon/Math/RingAverage.hpp>

#include <string>
#include <memory>
#include <list>


namespace Krayo {
namespace Internal {

class Engine
{
    using MapContainer = std::list<std::shared_ptr<Internal::Map>>;

    lkCommon::Math::RingAverage<float, 300> mAvgTime;

    Events::Manager mEventManager;
    Resource::Internal::Manager mResourceManager;
    Resource::Manager mResourceManagerAPI;
    Renderer::Renderer mRenderer;

    MapContainer mMaps;
    std::shared_ptr<Internal::Map> mCurrentMap;

    // captures CWD, navigates to app root dir and verifies if it's correct
    bool SetDirTree() const;
    void Update();

public:
    Engine();
    ~Engine();

    bool Init(const EngineDesc& desc);
    void MainLoop();

    std::shared_ptr<Internal::Map>& CreateMap(const std::string& name);
    void SetCurrentMap(std::shared_ptr<Internal::Map>& map);

    Resource::Manager& GetResourceManager();

    bool RegisterToEvent(const Events::ID id, Events::ISubscriber* subscriber);
    void EmitEvent(const Events::ID id, const Events::IMessage* message);
};

} // namespace Internal
} // namespace Krayo
