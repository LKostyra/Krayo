#pragma once

#include "Renderer/LowLevel/Instance.hpp"
#include "Renderer/LowLevel/Device.hpp"
#include "Renderer/LowLevel/Backbuffer.hpp"
#include "Renderer/LowLevel/Tools.hpp"

#include "Math/Frustum.hpp"

#include "Scene/Camera.hpp"
#include "Scene/Mesh.hpp"
#include "Scene/Map.hpp"

#include "Renderer/HighLevel/GridFrustumsGenerator.hpp"
#include "Renderer/HighLevel/ParticleEngine.hpp"
#include "Renderer/HighLevel/DepthPrePass.hpp"
#include "Renderer/HighLevel/LightCuller.hpp"
#include "Renderer/HighLevel/ForwardPass.hpp"
#include "Renderer/HighLevel/ParticlePass.hpp"

#include <lkCommon/System/Window.hpp>
#include <lkCommon/Math/Matrix4.hpp>


namespace Krayo {
namespace Renderer {

struct RendererDesc
{
    bool debugEnable;
    bool debugVerbose;
    bool vsync;
    bool noAsync;
    float fov;
    float nearZ;
    float farZ;
    lkCommon::System::Window* window;

    RendererDesc()
        : debugEnable(false)
        , debugVerbose(false)
        , vsync(false)
        , noAsync(false)
        , fov(60.0f)
        , nearZ(0.1f)
        , farZ(100.0f)
        , window(nullptr)
    {}
};

class Renderer final
{
    InstancePtr mInstance;
    DevicePtr mDevice;

    Backbuffer mBackbuffer;
    VkRAII<VkSemaphore> mImageAcquiredSem;
    VkRAII<VkSemaphore> mParticleEngineSem;
    VkRAII<VkSemaphore> mDepthSem;
    VkRAII<VkSemaphore> mCullingSem;
    VkRAII<VkSemaphore> mRenderSem;
    VkRAII<VkSemaphore> mParticlePassSem;
    VkRAII<VkFence> mParticleEngineFence;
    VkRAII<VkFence> mFrameFence;

    lkCommon::Math::Matrix4 mProjection;
    VkRAII<VkDescriptorSetLayout> mVertexShaderLayout;
    VkDescriptorSet mVertexShaderSet;
    Buffer mVertexShaderCBuffer;
    RingBuffer mRingBuffer;
    Buffer mLightContainer;

    GridFrustumsGenerator mGridFrustumsGenerator;
    //ParticleEngine mParticleEngine;
    DepthPrePass mDepthPrePass;
    LightCuller mLightCuller;
    ForwardPass mForwardPass;
    //ParticlePass mParticlePass;

public:
    Renderer();
    ~Renderer();

    bool Init(const RendererDesc& desc);
    void Draw(const Scene::Internal::Map& map, const Scene::Internal::Camera& camera, float deltaTime, float interpolation);

    // this function should be used only when application finishes
    void WaitForAll() const;
};

} // namespace Renderer
} // namespace Krayo
