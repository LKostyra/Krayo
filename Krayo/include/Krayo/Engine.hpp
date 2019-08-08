#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/Events.hpp"
#include "Krayo/Map.hpp"


namespace Krayo {

/**
 * Describes how engine is supposed to be initalized
 */
struct EngineDesc
{
    /**
     * Enables debug mode.
     */
    bool debug;

    /**
     * Enables verbose logging. Respected only when @p debug is true.
     */
    bool debugVerbose;

    /**
     * Enables vertical sync.
     */
    bool vsync;

    /**
     * Engine window's width
     */
    uint32_t windowWidth;

    /**
     * Engine window's height
     */
    uint32_t windowHeight;

    EngineDesc()
        : debug(false)
        , debugVerbose(false)
        , vsync(true)
        , windowWidth(640)
        , windowHeight(480)
    {
    }
};

class Engine final
{
    class Impl;
    Engine::Impl* mImpl;

public:
    KRAYO_API Engine();
    KRAYO_API ~Engine();

    /**
     * Initialize Engine instance
     *
     * @p[in] desc Initial properties of the Engine
     * @return True if initialization succeeded, false in case of error.
     */
    KRAYO_API bool Init(const EngineDesc& desc);

    /**
     * Enter Engine's main loop.
     *
     * This function exits automatically when Engine's window is closed.
     */
    KRAYO_API void MainLoop();

    /**
     * Create an empty Map.
     *
     * @p[in] name Name to be given to a map.
     * @return Pointer to a Map object, nullptr on error.
     */
    KRAYO_API Krayo::Map* CreateMap(const std::string& name);

    /**
     * Set current Map for Engine to work on.
     *
     * @p[in] map Engine's Map to be made current.
     */
    KRAYO_API void SetCurrentMap(Krayo::Map* map);

    /**
     * Acquire current map.
     *
     * @return Map currently being processed by Engine.
     */
    KRAYO_API Krayo::Map* GetCurrentMap();

    /**
     * Create new Material;
     */
    KRAYO_API Krayo::Material* CreateMaterial(const std::string& name);

    /**
     * @defgroup EventAPI Event API
     * @{
     */

    /**
     * Register Event Context to an event.
     *
     * @p[in] id         ID of an event to register to.
     * @p[in] subscriber Subscriber to an event, which will be used in case an Event appears.
     *                   Must be an extension of Krayo::Events::ISubscriber class.
     *
     * @note @p subscriber pointer is captured by std::unique_ptr in-engine, so caller does not
     *       have to worry about freeing the pointer after the app is done.
     */
    KRAYO_API bool RegisterToEvent(const Events::ID id, Events::ISubscriber* subscriber);

    /**
     * Emit a custom event.
     *
     * @p[in] message Message to emit to registered objects.
     */
    KRAYO_API void EmitEvent(const Events::ID id, const Events::IMessage* message);

    /**
     * @}
     */
};

} // namespace Krayo
