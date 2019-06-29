#pragma once

#include "Krayo/Events.hpp"

#include <vector>
#include <map>
#include <list>
#include <memory>


namespace Krayo {
namespace Events {


class EventManager
{
    using EventSubscribers = std::vector<std::unique_ptr<IEventSubscriber>>;
    using BuiltInEvents = std::vector<EventSubscribers>;
    using CustomEvents = std::map<EventID, EventSubscribers>;

    BuiltInEvents mBuiltInEvents;
    CustomEvents mCustomEvents;

public:
    EventManager() = default;
    ~EventManager() = default;

    void Init();

    bool RegisterToEvent(EventID id, IEventSubscriber* subscriber);
    void EmitEvent(IEventMessage* message);
};


} // namespace Krayo
} // namespace Events
