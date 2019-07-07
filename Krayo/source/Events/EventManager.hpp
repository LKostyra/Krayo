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
    using EventSubscribers = std::vector<std::unique_ptr<ISubscriber>>;
    using BuiltInEvents = std::vector<EventSubscribers>;
    using CustomEvents = std::map<ID, EventSubscribers>;

    BuiltInEvents mBuiltInEvents;
    CustomEvents mCustomEvents;

public:
    EventManager() = default;
    ~EventManager() = default;

    void Init();

    bool RegisterToEvent(const ID id, ISubscriber* subscriber);
    void EmitEvent(const ID id, const IMessage* message);
};


} // namespace Krayo
} // namespace Events
