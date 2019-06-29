#pragma once

#include <memory>


namespace Krayo {

/**
 * ID of Event to register to.
 *
 * Reserved Event ID values are from 0x00000000 to 0x7FFFFFFF.
 *
 * Values from 0x80000000 to 0xFFFFFFFF are free to use by application developers.
 */
enum class EventID: unsigned int
{
    Unknown = 0,
    BuiltInCount, //< Count of built in event ID's
};

/**
 * Helper macro to cast custom Event ID's
 */
#define EVENT_ID(x) static_cast<EventID>(x)


class IEventMessage
{
public:
    virtual ~IEventMessage() {}

    virtual const EventID GetID() const = 0;
};


class IEventSubscriber
{
public:
    virtual ~IEventSubscriber() {}

    virtual void Call(IEventMessage* message) = 0;
};

} // namespace Krayo
