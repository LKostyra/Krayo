#pragma once

#include "Prerequisites.hpp"
#include "Renderer/LowLevel/Device.hpp"
#include "Renderer/LowLevel/Framebuffer.hpp"
#include "Renderer/LowLevel/Buffer.hpp"
#include "Renderer/LowLevel/Texture.hpp"
#include "Renderer/LowLevel/Device.hpp"
#include "Renderer/LowLevel/Types.hpp"


namespace Krayo {
namespace Renderer {

class CommandBuffer
{
    friend class Device;
    friend class Texture;
    friend class Backbuffer;

    DevicePtr mDevice;
    VkCommandPool mOwningPool;
    VkCommandBuffer mCommandBuffer;
    Framebuffer* mCurrentFramebuffer;

public:
    CommandBuffer();
    ~CommandBuffer();

    bool Init(const DevicePtr& device, DeviceQueueType queueType);

    void Barrier(VkPipelineStageFlags fromStage, VkPipelineStageFlags toStage,
                 VkAccessFlags accessFrom, VkAccessFlags accessTo);
    void BufferBarrier(const Buffer* buffer, VkPipelineStageFlags fromStage, VkPipelineStageFlags toStage,
                       VkAccessFlags accessFrom, VkAccessFlags accessTo,
                       uint32_t fromQueueFamily, uint32_t toQueueFamily);
    void ImageBarrier(const Texture* texture, VkPipelineStageFlags fromStage, VkPipelineStageFlags toStage,
                      VkAccessFlags accessFrom, VkAccessFlags accessTo,
                      VkImageLayout fromLayout, VkImageLayout toLayout,
                      uint32_t fromQueueFamily, uint32_t toQueueFamily);
    void ImageBarrier(const Backbuffer* backbuffer, VkPipelineStageFlags fromStage, VkPipelineStageFlags toStage,
                      VkAccessFlags accessFrom, VkAccessFlags accessTo,
                      VkImageLayout fromLayout, VkImageLayout toLayout,
                      uint32_t fromQueueFamily, uint32_t toQueueFamily);
    void Begin();
    void BeginRenderPass(VkRenderPass rp, Framebuffer* fb, ClearType types, float clearValues[4], float depthValue = 0.0f);
    void BindVertexBuffer(const Buffer* buffer, uint32_t binding, VkDeviceSize offset);
    void BindIndexBuffer(const Buffer* buffer);
    void BindPipeline(VkPipeline pipeline, VkPipelineBindPoint point);
    void BindDescriptorSet(VkDescriptorSet set, VkPipelineBindPoint point, uint32_t setSlot, VkPipelineLayout layout);
    void BindDescriptorSet(VkDescriptorSet set, VkPipelineBindPoint point, uint32_t setSlot, VkPipelineLayout layout, uint32_t dynamicOffset);
    void Clear(ClearType types, float clearValues[4], float depthValue);
    void CopyBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size);
    void CopyBufferToTexture(Buffer* src, Texture* dst);
    void CopyTexture(Texture* src, Texture* dst);
    void CopyTextureToBackbuffer(Texture* src, Backbuffer* dst);
    void Dispatch(uint32_t x, uint32_t y, uint32_t z);
    void Draw(uint32_t vertCount, uint32_t instanceCount);
    void DrawIndexed(uint32_t vertCount);
    void EndRenderPass();
    bool End();
    void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height, float minDepth, float maxDepth);
    void SetScissor(int32_t x, int32_t y, uint32_t width, uint32_t height);
};

} // namespace Renderer
} // namespace Krayo
