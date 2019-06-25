#pragma once

#include "Krayo/Engine.hpp"

#include "Renderer/HighLevel/Renderer.hpp"


namespace Krayo {

class Engine::Impl
{
    Renderer::Renderer mRenderer;
    Scene::Scene mScene;
    Scene::Camera mCamera;

    // captures CWD, navigates to app root dir and verifies if it's correct
    bool SetDirTree() const;

public:
    Impl();
    ~Impl();

    bool Init(const EngineDesc& desc);
    void Draw(const float frameTime);
};

} // namespace Krayo
