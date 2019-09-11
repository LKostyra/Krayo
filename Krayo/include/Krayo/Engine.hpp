#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include "Krayo/Events.hpp"
#include "Krayo/Scene/Map.hpp"
#include "Krayo/Resource/Manager.hpp"

#include <memory>


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
    std::unique_ptr<Impl> mImpl;

public:
    /**
     * Construct Engine instance.
     */
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
     * Create a new Map
     *
     * @p[in] name Name of map to create.
     * @return Map object
     */
    KRAYO_API Krayo::Scene::Map CreateMap(const std::string& name);

    /**
     * Get map
     */
    KRAYO_API Krayo::Scene::Map GetMap(const std::string& name);

    /**
     * Set map to draw (or unset)
     *
     * @p[in] name Name of map to be set to draw
     * @return True on success, false when map is not found.
     */
    KRAYO_API void SetCurrentMap(const Krayo::Scene::Map& map);

    /**
     * Acquire Engine's resource manager
     */
    KRAYO_API Krayo::Resource::Manager& GetResourceManager();

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
