#pragma once

#include "Krayo/ApiDef.hpp"

#include <memory>


namespace Krayo {
namespace Events {

/**
 * ID of Event to register to.
 *
 * Reserved Event ID values are from 0x00000000 to 0x7FFFFFFF.
 *
 * Values from 0x80000000 to 0xFFFFFFFF are free to use by application developers.
 */
enum class ID: unsigned int
{
    Unknown = 0,
    Tick,
    KeyDown,
    KeyUp,
    MouseDown,
    MouseUp,
    MouseMove,
    BuiltInCount, //< Count of built in event ID's
};

/**
 * Helper macro to cast custom Event ID's
 */
#define EVENT_ID(x) static_cast<ID>(x)


/**
 * Abstraction layer for Event messages
 *
 */
class KRAYO_API IMessage
{
public:
    virtual ~IMessage() {}

    virtual const ID GetID() const = 0;
};


/**
 * Abstraction layer for Event subscribers.
 *
 * Inherit this object and provide whichever additional data you require in order to properly
 * process the event.
 */
class KRAYO_API ISubscriber
{
public:
    virtual ~ISubscriber() {}

    virtual void Call(const IMessage* message) = 0;
};




/**
 * @defgroup EventMessages Event API standard messages
 *
 * Group contains standard events emitted by Krayo.
 * @{
 */

/**
 * KeyDown event message. Emitted when a keyboard button is pushed down by user.
 *
 * @p mKeyID Contains pressed key ID.
 */
class KRAYO_API KeyDownMessage: public IMessage
{
    int mKeyID; // FIXME replace with Krayo::KeyCode type

public:
    KeyDownMessage(int keyID): mKeyID(keyID) {}
    ~KeyDownMessage() {};

    const ID GetID() const override { return ID::KeyDown; }
    const int GetKeyID() const { return mKeyID; }
};

/**
 * KeyUp event message. Emitted when user lets go of previously pushed keyboard key.
 *
 * @p mKeyID Contains ID of key that was let go.
 */
class KRAYO_API KeyUpMessage: public IMessage
{
    int mKeyID; // FIXME replace with Krayo::KeyCode type

public:
    KeyUpMessage(int keyID): mKeyID(keyID) {}
    ~KeyUpMessage() {};

    const ID GetID() const override { return ID::KeyUp; }
    const int GetKeyID() const { return mKeyID; }
};

/**
 * MouseDown event message. Emitted when a mouse button is pushed down by user.
 *
 * @p mKeyID Contains pressed key ID.
 */
class KRAYO_API MouseDownMessage: public IMessage
{
    int mKeyID; // FIXME replace with Krayo::KeyCode type

public:
    MouseDownMessage(int keyID): mKeyID(keyID) {}
    ~MouseDownMessage() {};

    const ID GetID() const override { return ID::MouseDown; }
    const int GetKeyID() const { return mKeyID; }
};

/**
 * MouseUp event message. Emitted when user lets go of previously pushed mouse button.
 *
 * @p mKeyID Contains ID of key that was let go.
 */
class KRAYO_API MouseUpMessage: public IMessage
{
    int mKeyID; // FIXME replace with Krayo::KeyCode type

public:
    MouseUpMessage(int keyID): mKeyID(keyID) {}
    ~MouseUpMessage() {};

    const ID GetID() const override { return ID::MouseUp; }
    const int GetKeyID() const { return mKeyID; }
};

/**
 * MouseMove event message. Emitted when user moves its mouse.
 *
 * @p mPosX   Current X position of mouse cursor.
 * @p mPosY   Current Y position of mouse cursor.
 * @p mDeltaX Difference between previous and current X position of mouse cursor.
 * @p mDeltaY Difference between previous and current Y position of mouse cursor.
 */
class KRAYO_API MouseMoveMessage: public IMessage
{
    uint32_t mPosX;
    uint32_t mPosY;
    int32_t mDeltaX;
    int32_t mDeltaY;

public:
    MouseMoveMessage(uint32_t x, uint32_t y, int32_t deltaX, int32_t deltaY)
        : mPosX(x), mPosY(y), mDeltaX(deltaX), mDeltaY(deltaY) {}
    ~MouseMoveMessage() {};

    const ID GetID() const override { return ID::MouseMove; }
    const uint32_t GetPosX() const { return mPosX; }
    const uint32_t GetPosY() const { return mPosY; }
    const int32_t GetDeltaX() const { return mDeltaX; }
    const int32_t GetDeltaY() const { return mDeltaY; }
};


/**
 * @}
 */

} // namespace Events
} // namespace Krayo
