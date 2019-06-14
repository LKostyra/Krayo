#pragma once

#include "Krayo/Engine.hpp"

#include "Renderer/HighLevel/Renderer.hpp"


namespace Krayo {

class Engine::Impl
{
    Renderer::Renderer mRenderer;
    Scene::Scene mScene;
    Scene::Camera mCamera;

public:
    Impl();
    ~Impl();

    bool Init(const EngineDesc& desc);
    void Draw(const float frameTime);
};

} // namespace Krayo
