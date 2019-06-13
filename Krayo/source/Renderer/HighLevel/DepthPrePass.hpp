#pragma once

#include "Renderer/LowLevel/Texture.hpp"
#include "Renderer/LowLevel/Framebuffer.hpp"
#include "Renderer/LowLevel/Buffer.hpp"
#include "Renderer/LowLevel/Shader.hpp"
#include "Renderer/LowLevel/CommandBuffer.hpp"
#include "Renderer/LowLevel/VertexLayout.hpp"
#include "Renderer/LowLevel/RingBuffer.hpp"
#include "Renderer/LowLevel/MultiPipeline.hpp"
#include "Renderer/LowLevel/Tools.hpp"

#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"


namespace Krayo {
namespace Renderer {

struct DepthPrePassDesc
{
    uint32_t width;
    uint32_t height;
    VkDescriptorSetLayout vertexShaderLayout;

    DepthPrePassDesc()
        : width(0)
        , height(0)
        , vertexShaderLayout(VK_NULL_HANDLE)
    {
    }
};

struct DepthPrePassDrawDesc
{
    RingBuffer* ringBufferPtr;
    VkDescriptorSet vertexShaderSet;
    VkSemaphore signalSem;

    DepthPrePassDrawDesc()
        : ringBufferPtr(nullptr)
        , vertexShaderSet(VK_NULL_HANDLE)
        , signalSem(VK_NULL_HANDLE)
    {
    }
};

class DepthPrePass final
{
    DevicePtr mDevice;

    Texture mDepthTexture;
    Framebuffer mFramebuffer;
    VertexLayout mVertexLayout;
    MultiPipeline mPipeline;
    CommandBuffer mCommandBuffer;

    VkRAII<VkRenderPass> mRenderPass;
    VkRAII<VkPipelineLayout> mPipelineLayout;

public:
    bool Init(const DevicePtr& device, const DepthPrePassDesc& desc);
    void Draw(const Scene::Scene& scene, const DepthPrePassDrawDesc& desc);

    LKCOMMON_INLINE Texture* GetDepthTexture()
    {
        return &mDepthTexture;
    }
};

} // namespace Renderer
} // namespace Krayo
