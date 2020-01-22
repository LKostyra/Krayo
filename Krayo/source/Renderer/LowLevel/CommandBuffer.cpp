#include "Renderer/LowLevel/CommandBuffer.hpp"

#include "Renderer/LowLevel/Util.hpp"
#include "Renderer/LowLevel/Extensions.hpp"

#include "Renderer/HighLevel/Renderer.hpp"

#include <cstring>

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Renderer {

CommandBuffer::CommandBuffer()
    : mOwningPool(VK_NULL_HANDLE)
    , mCommandBuffer(VK_NULL_HANDLE)
    , mCurrentFramebuffer(nullptr)
{
}

CommandBuffer::~CommandBuffer()
{
    if (mCommandBuffer != VK_NULL_HANDLE)
        vkFreeCommandBuffers(mDevice->GetDevice(), mOwningPool, 1, &mCommandBuffer);
}

bool CommandBuffer::Init(const DevicePtr& device, DeviceQueueType queueType)
{
    mDevice = device;
    mOwningPool = mDevice->GetCommandPool(queueType);

    VkCommandBufferAllocateInfo allocInfo;
    LKCOMMON_ZERO_MEMORY(allocInfo);
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;
    allocInfo.commandPool = mOwningPool;
    VkResult result = vkAllocateCommandBuffers(mDevice->GetDevice(), &allocInfo, &mCommandBuffer);
    RETURN_FALSE_IF_FAILED(result, "Failed to allocate Command Buffer");

    return true;
}

void CommandBuffer::Barrier(VkPipelineStageFlags fromStage, VkPipelineStageFlags toStage,
                            VkAccessFlags accessFrom, VkAccessFlags accessTo)
{
    LOGC("stages: " << fromStage << " -> " << toStage <<
         "; accesses: " << accessFrom << " -> " << accessTo);

    VkMemoryBarrier barrier;
    LKCOMMON_ZERO_MEMORY(barrier);
    barrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
    barrier.srcAccessMask = accessFrom;
    barrier.dstAccessMask = accessTo;

    vkCmdPipelineBarrier(mCommandBuffer, fromStage, toStage, 0, 1, &barrier, 0, nullptr, 0, nullptr);
}

void CommandBuffer::BufferBarrier(const Buffer* buffer, VkPipelineStageFlags fromStage, VkPipelineStageFlags toStage,
                                  VkAccessFlags accessFrom, VkAccessFlags accessTo,
                                  uint32_t fromQueueFamily, uint32_t toQueueFamily)
{
    LOGC("buffer: " << reinterpret_cast<const void*>(buffer) <<
         "; stages: " << fromStage << " -> " << toStage <<
         "; accesses: " << accessFrom << " -> " << accessTo <<
         "; queue families: " << TranslateDeviceQueueTypeToString(fromQueueFamily) <<
         " -> " << TranslateDeviceQueueTypeToString(toQueueFamily));

    VkBufferMemoryBarrier barrier;
    LKCOMMON_ZERO_MEMORY(barrier);
    barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    barrier.buffer = buffer->GetBuffer();
    barrier.size = buffer->GetSize();
    barrier.srcAccessMask = accessFrom;
    barrier.dstAccessMask = accessTo;
    barrier.srcQueueFamilyIndex = fromQueueFamily;
    barrier.dstQueueFamilyIndex = toQueueFamily;

    vkCmdPipelineBarrier(mCommandBuffer, fromStage, toStage, 0, 0, nullptr, 1, &barrier, 0, nullptr);
}

void CommandBuffer::ImageBarrier(const Texture* texture, VkPipelineStageFlags fromStage, VkPipelineStageFlags toStage,
                                 VkAccessFlags accessFrom, VkAccessFlags accessTo,
                                 VkImageLayout fromLayout, VkImageLayout toLayout,
                                 uint32_t fromQueueFamily, uint32_t toQueueFamily)
{
    LOGC("texture: " << reinterpret_cast<const void*>(texture) <<
         "; stages: " << fromStage << " -> " << toStage <<
         "; accesses: " << accessFrom << " -> " << accessTo <<
         "; layouts: " << TranslateVkImageLayoutToString(fromLayout) <<
         " -> " << TranslateVkImageLayoutToString(toLayout) <<
         "; queue families: " << TranslateDeviceQueueTypeToString(fromQueueFamily) <<
         " -> " << TranslateDeviceQueueTypeToString(toQueueFamily));

    VkImageMemoryBarrier barrier;
    LKCOMMON_ZERO_MEMORY(barrier);
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.image = texture->mImage;
    barrier.subresourceRange = texture->mSubresourceRange;
    barrier.oldLayout = fromLayout;
    barrier.newLayout = toLayout;
    barrier.srcAccessMask = accessFrom;
    barrier.dstAccessMask = accessTo;
    barrier.srcQueueFamilyIndex = fromQueueFamily;
    barrier.dstQueueFamilyIndex = toQueueFamily;

    vkCmdPipelineBarrier(mCommandBuffer, fromStage, toStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);
}

void CommandBuffer::ImageBarrier(const Backbuffer* backbuffer, VkPipelineStageFlags fromStage, VkPipelineStageFlags toStage,
                                 VkAccessFlags accessFrom, VkAccessFlags accessTo,
                                 VkImageLayout fromLayout, VkImageLayout toLayout,
                                 uint32_t fromQueueFamily, uint32_t toQueueFamily)
{
    LOGC("backbuffer: " << reinterpret_cast<const void*>(backbuffer) <<
         "; stages: " << fromStage << " -> " << toStage <<
         "; accesses: " << accessFrom << " -> " << accessTo <<
         "; layouts: " << TranslateVkImageLayoutToString(fromLayout) <<
         " -> " << TranslateVkImageLayoutToString(toLayout) <<
         "; queue families: " << TranslateDeviceQueueTypeToString(fromQueueFamily) <<
         " -> " << TranslateDeviceQueueTypeToString(toQueueFamily));

    VkImageMemoryBarrier barrier;
    LKCOMMON_ZERO_MEMORY(barrier);
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.image = backbuffer->mImages[backbuffer->mCurrentBuffer].image;
    barrier.subresourceRange = backbuffer->mSubresourceRange;
    barrier.oldLayout = fromLayout;
    barrier.newLayout = toLayout;
    barrier.srcAccessMask = accessFrom;
    barrier.dstAccessMask = accessTo;
    barrier.srcQueueFamilyIndex = fromQueueFamily;
    barrier.dstQueueFamilyIndex = toQueueFamily;

    vkCmdPipelineBarrier(mCommandBuffer, fromStage, toStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);
}

void CommandBuffer::Begin()
{
    LOGC('-');

    VkCommandBufferBeginInfo beginInfo;
    LKCOMMON_ZERO_MEMORY(beginInfo);
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(mCommandBuffer, &beginInfo);
}

void CommandBuffer::BeginRenderPass(VkRenderPass rp, Framebuffer* fb, ClearType types, float clearValues[4], float depthValue)
{
    LOGC("render pass " << reinterpret_cast<void*>(rp) <<
         "; framebuffer " << reinterpret_cast<void*>(fb) <<
         "; clear types " << static_cast<uint32_t>(types));

    VkClearValue clear[2];
    uint32_t clearCount = 0;

    if (types & ClearType::COLOR)
    {
        LKCOMMON_ASSERT(clearValues != nullptr, "clearValues pointer was NULL while attempting to clear color texture!");
        memcpy(clear[clearCount].color.float32, clearValues, 4 * sizeof(float));
        clearCount++;
    }

    if (types & ClearType::DEPTH)
    {
        clear[clearCount].depthStencil.depth = depthValue;
        clearCount++;
    }

    VkRenderPassBeginInfo rpInfo;
    LKCOMMON_ZERO_MEMORY(rpInfo);
    rpInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpInfo.renderPass = rp;
    rpInfo.renderArea.extent.width = fb->mWidth;
    rpInfo.renderArea.extent.height = fb->mHeight;
    rpInfo.clearValueCount = clearCount;
    rpInfo.pClearValues = clear;
    rpInfo.framebuffer = fb->mFramebuffer;
    vkCmdBeginRenderPass(mCommandBuffer, &rpInfo, VK_SUBPASS_CONTENTS_INLINE);

    mCurrentFramebuffer = fb;
}

void CommandBuffer::BindVertexBuffer(const Buffer* buffer, uint32_t binding, VkDeviceSize offset)
{
    LKCOMMON_ASSERT(buffer != nullptr, "Provided buffer is null");
    LKCOMMON_ASSERT(buffer->mBuffer != VK_NULL_HANDLE, "Provided buffer is not initialized");

    vkCmdBindVertexBuffers(mCommandBuffer, binding, 1, &buffer->mBuffer, &offset);
}

void CommandBuffer::BindIndexBuffer(const Buffer* buffer)
{
    LKCOMMON_ASSERT(buffer != nullptr, "Provided buffer is null");
    LKCOMMON_ASSERT(buffer->mBuffer != VK_NULL_HANDLE, "Provided buffer is not initialized");

    vkCmdBindIndexBuffer(mCommandBuffer, buffer->mBuffer, 0, VK_INDEX_TYPE_UINT32);
}

void CommandBuffer::BindPipeline(VkPipeline pipeline, VkPipelineBindPoint point)
{
    LKCOMMON_ASSERT(pipeline != VK_NULL_HANDLE, "Provided pipeline is not initialized");

    vkCmdBindPipeline(mCommandBuffer, point, pipeline);
}

void CommandBuffer::BindDescriptorSet(VkDescriptorSet set, VkPipelineBindPoint point, uint32_t setSlot, VkPipelineLayout layout)
{
    LKCOMMON_ASSERT(set != VK_NULL_HANDLE, "Provided descriptor set is not initialized");
    LKCOMMON_ASSERT(layout != VK_NULL_HANDLE, "Provided pipeline layout is not initialized");

    vkCmdBindDescriptorSets(mCommandBuffer, point, layout, setSlot, 1, &set, 0, nullptr);
}

void CommandBuffer::BindDescriptorSet(VkDescriptorSet set, VkPipelineBindPoint point, uint32_t setSlot, VkPipelineLayout layout, uint32_t dynamicOffset)
{
    LKCOMMON_ASSERT(set != VK_NULL_HANDLE, "Provided descriptor set is not initialized");
    LKCOMMON_ASSERT(layout != VK_NULL_HANDLE, "Provided pipeline layout is not initialized");

    vkCmdBindDescriptorSets(mCommandBuffer, point, layout, setSlot, 1, &set, 1, &dynamicOffset);
}

void CommandBuffer::Clear(ClearType types, float clearValues[4], float depthValue)
{
    VkClearAttachment clearAtt[2];
    uint32_t clearAttCount = 0;

    if (types & ClearType::COLOR)
    {
        LKCOMMON_ZERO_MEMORY(clearAtt[clearAttCount]);
        clearAtt[clearAttCount].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        clearAtt[clearAttCount].colorAttachment = 0;
        memcpy(clearAtt[clearAttCount].clearValue.color.float32, clearValues, 4 * sizeof(float));
        clearAttCount++;
    }

    if (types & ClearType::DEPTH)
    {
        LKCOMMON_ZERO_MEMORY(clearAtt[clearAttCount]);
        clearAtt[clearAttCount].aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        clearAtt[clearAttCount].clearValue.depthStencil.depth = depthValue;
        clearAttCount++;
    }

    VkClearRect rect;
    rect.rect.offset = { 0, 0 };
    rect.rect.extent = { mCurrentFramebuffer->mWidth , mCurrentFramebuffer->mHeight };
    rect.baseArrayLayer = 0;
    rect.layerCount = 1;

    vkCmdClearAttachments(mCommandBuffer, clearAttCount, clearAtt, 1, &rect);
}

void CommandBuffer::CopyBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size)
{
    LKCOMMON_ASSERT(src != VK_NULL_HANDLE, "Provided source buffer is not initialized");
    LKCOMMON_ASSERT(dst != VK_NULL_HANDLE, "Provided destination buffer is not initialized");

    VkBufferCopy region;
    LKCOMMON_ZERO_MEMORY(region);
    region.size = size;
    vkCmdCopyBuffer(mCommandBuffer, src, dst, 1, &region);
}

void CommandBuffer::CopyBufferToTexture(Buffer* src, Texture* dst)
{
    LKCOMMON_ASSERT(src != nullptr, "Provided source buffer is null");
    LKCOMMON_ASSERT(src->mBuffer != VK_NULL_HANDLE, "Provided source buffer is not initialized");
    LKCOMMON_ASSERT(dst != nullptr, "Provided destination texture is null");
    LKCOMMON_ASSERT(dst->mImage != VK_NULL_HANDLE, "Provided destination texture is not initialized");

    std::vector<VkBufferImageCopy> regions;

    uint32_t width = dst->mWidth;
    uint32_t height = dst->mHeight;
    uint32_t offset = 0;

    VkBufferImageCopy region;
    LKCOMMON_ZERO_MEMORY(region);
    for (uint32_t i = 0; i < dst->mSubresourceRange.levelCount; ++i)
    {
        region.bufferOffset = offset;
        region.imageExtent.width = width;
        region.imageExtent.height = height;
        region.imageExtent.depth = 1;
        region.imageSubresource.aspectMask = dst->mSubresourceRange.aspectMask;
        region.imageSubresource.baseArrayLayer = dst->mSubresourceRange.baseArrayLayer;
        region.imageSubresource.layerCount = dst->mSubresourceRange.layerCount;
        region.imageSubresource.mipLevel = i;

        regions.push_back(region);

        offset += width * height * TranslateVkFormatToFormatSize(dst->mFormat);
        width >>= 1;
        height >>= 1;
    }

    vkCmdCopyBufferToImage(mCommandBuffer, src->GetBuffer(), dst->GetImage(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                           static_cast<uint32_t>(regions.size()), regions.data());
}

void CommandBuffer::CopyTexture(Texture* src, Texture* dst)
{
    LKCOMMON_ASSERT(src->mWidth == dst->mWidth, "Textures must have same dimensions for copy operation");
    LKCOMMON_ASSERT(src->mHeight == dst->mHeight, "Textures must have same dimensions for copy operation");
    LKCOMMON_ASSERT(src->mFormat == dst->mFormat, "Textures must have same format for copy operation");
    LKCOMMON_ASSERT(src->mImage != VK_NULL_HANDLE, "Provided source texture is not initialized");
    LKCOMMON_ASSERT(dst->mImage != VK_NULL_HANDLE, "Provided destination texture is not initialized");

    VkImageCopy region;
    LKCOMMON_ZERO_MEMORY(region);
    region.extent.width = src->GetWidth();
    region.extent.height = src->GetHeight();
    region.extent.depth = 1;
    region.srcSubresource.aspectMask = src->mSubresourceRange.aspectMask;
    region.srcSubresource.baseArrayLayer = src->mSubresourceRange.baseArrayLayer;
    region.srcSubresource.layerCount = src->mSubresourceRange.layerCount;
    region.srcSubresource.mipLevel = 0;
    region.dstSubresource.aspectMask = dst->mSubresourceRange.aspectMask;
    region.dstSubresource.baseArrayLayer = dst->mSubresourceRange.baseArrayLayer;
    region.dstSubresource.layerCount = dst->mSubresourceRange.layerCount;
    region.dstSubresource.mipLevel = 0;
    vkCmdCopyImage(mCommandBuffer,
                   src->GetImage(), VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                   dst->GetImage(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                   1, &region);
}

void CommandBuffer::CopyTextureToBackbuffer(Texture* src, Backbuffer* dst)
{
    LKCOMMON_ASSERT(src->mWidth == dst->mWidth, "Textures must have same dimensions for copy operation");
    LKCOMMON_ASSERT(src->mHeight == dst->mHeight, "Textures must have same dimensions for copy operation");
    LKCOMMON_ASSERT(src->mFormat == dst->mFormat, "Textures must have same format for copy operation");
    LKCOMMON_ASSERT(src->mImage != VK_NULL_HANDLE, "Provided source texture is not initialized");
    LKCOMMON_ASSERT(!dst->mImages.empty(), "Provided Backbuffer is not initialized");

    VkImageCopy region;
    LKCOMMON_ZERO_MEMORY(region);
    region.extent.width = src->GetWidth();
    region.extent.height = src->GetHeight();
    region.extent.depth = 1;
    region.srcSubresource.aspectMask = src->mSubresourceRange.aspectMask;
    region.srcSubresource.baseArrayLayer = src->mSubresourceRange.baseArrayLayer;
    region.srcSubresource.layerCount = src->mSubresourceRange.layerCount;
    region.srcSubresource.mipLevel = 0;
    region.dstSubresource.aspectMask = dst->mSubresourceRange.aspectMask;
    region.dstSubresource.baseArrayLayer = dst->mSubresourceRange.baseArrayLayer;
    region.dstSubresource.layerCount = dst->mSubresourceRange.layerCount;
    region.dstSubresource.mipLevel = 0;
    vkCmdCopyImage(mCommandBuffer,
                   src->GetImage(), VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                   dst->mImages[dst->mCurrentBuffer].image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                   1, &region);
}

void CommandBuffer::Dispatch(uint32_t x, uint32_t y, uint32_t z)
{
    LOGC(x << 'x' << y << 'x' << z);
    vkCmdDispatch(mCommandBuffer, x, y, z);
}

void CommandBuffer::Draw(uint32_t vertCount, uint32_t instanceCount)
{
    LOGC(vertCount << " verts; " << instanceCount << " instances");
    vkCmdDraw(mCommandBuffer, vertCount, instanceCount, 0, 0);
}

void CommandBuffer::DrawIndexed(uint32_t indexCount)
{
    LOGC(indexCount << " indices");
    vkCmdDrawIndexed(mCommandBuffer, indexCount, 1, 0, 0, 0);
}

void CommandBuffer::EndRenderPass()
{
    LOGC('-');

    vkCmdEndRenderPass(mCommandBuffer);
    mCurrentFramebuffer = nullptr;
}

bool CommandBuffer::End()
{
    LOGC('-');

    VkResult result = vkEndCommandBuffer(mCommandBuffer);
    RETURN_FALSE_IF_FAILED(result, "Failure during Command Buffer recording");
    return true;
}

void CommandBuffer::SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height, float minDepth, float maxDepth)
{
    VkViewport viewport;
    viewport.x = static_cast<float>(x);
    viewport.y = static_cast<float>(y);
    viewport.width = static_cast<float>(width);
    viewport.height = static_cast<float>(height);
    viewport.minDepth = minDepth;
    viewport.maxDepth = maxDepth;
    vkCmdSetViewport(mCommandBuffer, 0, 1, &viewport);
}

void CommandBuffer::SetScissor(int32_t x, int32_t y, uint32_t width, uint32_t height)
{
    VkRect2D scissor;
    scissor.offset.x = x;
    scissor.offset.y = y;
    scissor.extent.width = width;
    scissor.extent.height = height;
    vkCmdSetScissor(mCommandBuffer, 0, 1, &scissor);
}

} // namespace Renderer
} // namespace Krayo
