#pragma once

#include "Krayo/ApiDef.hpp"

#include <lkCommon/System/Window.hpp>


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
     * Pointer to Window to which Engine should render.
     */
    lkCommon::System::Window* window; // TODO THIS MUST BE REMOVED, Krayo should only set out its independent api

    EngineDesc()
        : debug(false)
        , debugVerbose(false)
        , vsync(true)
        , window(nullptr)
    {
    }
};

class KRAYO_API Engine final
{
    class Impl;
    Engine::Impl* mImpl;

public:
    Engine();
    ~Engine();

    bool Init(const EngineDesc& desc);
    void Draw(const float frameTime) const;
};

} // namespace Krayo
