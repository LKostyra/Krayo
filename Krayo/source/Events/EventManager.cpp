#include "EventManager.hpp"

#include <lkCommon/lkCommon.hpp>


namespace Krayo {
namespace Events {

LKCOMMON_INLINE bool IsBuiltInEvent(EventID id)
{
    return !(static_cast<uint32_t>(id) & 0x80000000);
}

LKCOMMON_INLINE bool IsCustomEvent(EventID id)
{
    return !IsBuiltInEvent(id);
}

void EventManager::Init()
{
    mBuiltInEvents.resize(static_cast<uint32_t>(EventID::BuiltInCount));
}

bool EventManager::RegisterToEvent(EventID id, IEventSubscriber* subscriber)
{
    if (id == EventID::Unknown)
    {
        LOGE("Unknown Event ID");
        return false;
    }

    uint32_t castedId = static_cast<uint32_t>(id);

    if (IsBuiltInEvent(id))
    {
        LKCOMMON_ASSERT(static_cast<uint32_t>(id) < static_cast<uint32_t>(EventID::BuiltInCount), "Invalid built-in Event ID");

        mBuiltInEvents[castedId].emplace_back(subscriber);
    }
    else
    {
        // no verification for Event ID correctness here, since IDs can be arbitrary
        CustomEvents::iterator subs = mCustomEvents.find(id);
        if (subs == mCustomEvents.end())
        {
            // new event ID we don't know about yet
            // emplace new list of subscribers to our custom events map
            auto result = mCustomEvents.emplace(id, EventSubscribers());
            subs = result.first;
        }

        subs->second.emplace_back(subscriber);
    }

    return true;
}

void EventManager::EmitEvent(IEventMessage* message)
{
    EventID id = message->GetID();
    LKCOMMON_ASSERT(id != EventID::Unknown, "Invalid built-in Event ID");

    if (IsBuiltInEvent(id))
    {
        LKCOMMON_ASSERT(static_cast<uint32_t>(id) < static_cast<uint32_t>(EventID::BuiltInCount), "Invalid built-in Event ID");

        EventSubscribers& subs = mBuiltInEvents[static_cast<uint32_t>(id)];
        for (auto& s: subs)
        {
            s->Call(message);
        }
    }
    else
    {
        CustomEvents::iterator subs = mCustomEvents.find(id);
        LKCOMMON_ASSERT(subs != mCustomEvents.end(), "Unknown custom Event ID");

        for (auto& s: subs->second)
        {
            s->Call(message);
        }
    }
}

} // namespace Krayo
} // namespace Events
