#include "Renderer/LowLevel/Texture.hpp"

#include "Renderer/LowLevel/Util.hpp"
#include "Renderer/LowLevel/Extensions.hpp"
#include "Renderer/LowLevel/CommandBuffer.hpp"
#include "Renderer/LowLevel/DescriptorAllocator.hpp"
#include "Renderer/LowLevel/Tools.hpp"


namespace Krayo {
namespace Renderer {

Texture::Texture()
    : mDevice(nullptr)
    , mWidth(0)
    , mHeight(0)
    , mFormat(VK_FORMAT_UNDEFINED)
    , mImage(VK_NULL_HANDLE)
    , mImageView(VK_NULL_HANDLE)
    , mImageMemory(VK_NULL_HANDLE)
    , mImageDescriptorSet(VK_NULL_HANDLE)
{
}

Texture::~Texture()
{
    LOGM("Destroying Texture (image " << std::hex << mImage << " view " << mImageView << " res " << std::dec << mWidth << "x" << mHeight << ")");

    if (mImageMemory != VK_NULL_HANDLE)
        vkFreeMemory(mDevice->GetDevice(), mImageMemory, nullptr);
    if (mImageView != VK_NULL_HANDLE)
        vkDestroyImageView(mDevice->GetDevice(), mImageView, nullptr);
    if (mImage != VK_NULL_HANDLE)
        vkDestroyImage(mDevice->GetDevice(), mImage, nullptr);
}

bool Texture::Init(const DevicePtr& device, const TextureDesc& desc)
{
    mDevice = device;

    VkImageCreateInfo imageInfo;
    LKCOMMON_ZERO_MEMORY(imageInfo);
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.format = desc.format;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.mipLevels = desc.mipmapCount;
    imageInfo.extent.width = desc.width;
    imageInfo.extent.height = desc.height;
    imageInfo.extent.depth = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.usage = desc.usage;
    if (desc.data != nullptr) imageInfo.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
    VkResult result = vkCreateImage(mDevice->GetDevice(), &imageInfo, nullptr, &mImage);
    RETURN_FALSE_IF_FAILED(result, "Failed to create Image for texture");

    VkMemoryRequirements memReqs;
    vkGetImageMemoryRequirements(mDevice->GetDevice(), mImage, &memReqs);

    VkMemoryAllocateInfo memInfo;
    LKCOMMON_ZERO_MEMORY(memInfo);
    memInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memInfo.memoryTypeIndex = mDevice->GetMemoryTypeIndex(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    memInfo.allocationSize = memReqs.size;
    result = vkAllocateMemory(mDevice->GetDevice(), &memInfo, nullptr, &mImageMemory);
    RETURN_FALSE_IF_FAILED(result, "Failed to allocate memory for Image");

    result = vkBindImageMemory(mDevice->GetDevice(), mImage, mImageMemory, 0);
    RETURN_FALSE_IF_FAILED(result, "Binding Image memory to Image failed");

    LKCOMMON_ZERO_MEMORY(mSubresourceRange);
    if (desc.usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
        mSubresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    else
        mSubresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    mSubresourceRange.baseMipLevel = 0;
    mSubresourceRange.levelCount = desc.mipmapCount;
    mSubresourceRange.baseArrayLayer = 0;
    mSubresourceRange.layerCount = 1;

    mWidth = desc.width;
    mHeight = desc.height;
    mFormat = desc.format;

    Buffer tempBuffer;

    if (desc.data != nullptr)
    {
        VkDeviceSize dataSize = 0;
        for (uint32_t i = 0; i < desc.mipmapCount; ++i)
            dataSize += desc.data[i].dataSize;

        if (dataSize > memReqs.size)
        {
            LOGE("Not enough memory to initialize texture");
            return false;
        }

        BufferDesc tempBufferDesc;
        tempBufferDesc.type = BufferType::Dynamic;
        tempBufferDesc.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        tempBufferDesc.dataSize = dataSize;
        tempBufferDesc.ownerQueueFamily = desc.ownerQueueFamily;
        if (!tempBuffer.Init(mDevice, tempBufferDesc))
            return false;

        VkDeviceSize offset = 0;
        for (uint32_t i = 0; i < desc.mipmapCount; ++i)
        {
            tempBuffer.Write(desc.data[i].data, desc.data[i].dataSize, offset);
            offset += desc.data[i].dataSize;
        }
    }

    // transition Image to desired layout and eventually copy data to buffer
    // TODO OPTIMIZE this uses graphics queue and waits; after implementing queue manager, switch to Transfer queue
    CommandBuffer transitionCmdBuffer;
    if (!transitionCmdBuffer.Init(mDevice, desc.ownerQueueFamily))
        return false;

    transitionCmdBuffer.Begin();

    if (desc.data != nullptr)
    {
        transitionCmdBuffer.ImageBarrier(this,
                                         VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
                                         0, VK_ACCESS_TRANSFER_WRITE_BIT,
                                         VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                                         VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED);
        transitionCmdBuffer.CopyBufferToTexture(&tempBuffer, this);
        transitionCmdBuffer.ImageBarrier(this,
                                         VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                         VK_ACCESS_TRANSFER_WRITE_BIT, 0,
                                         VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, desc.layout,
                                         VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED);
    }
    else
    {
        transitionCmdBuffer.ImageBarrier(this,
                                         VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                         0, 0,
                                         VK_IMAGE_LAYOUT_PREINITIALIZED, desc.layout,
                                         VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED);
    }
    transitionCmdBuffer.End();

    // TODO this should happen on Transfer Queue (might involve copying which takes time)
    mDevice->Execute(desc.ownerQueueFamily, &transitionCmdBuffer);
    mDevice->Wait(desc.ownerQueueFamily); // TODO this should be removed


    VkImageViewCreateInfo ivInfo;
    LKCOMMON_ZERO_MEMORY(ivInfo);
    ivInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    ivInfo.image = mImage;
    ivInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    ivInfo.format = desc.format;
    ivInfo.subresourceRange = mSubresourceRange;
    ivInfo.components = {
        VK_COMPONENT_SWIZZLE_R,
        VK_COMPONENT_SWIZZLE_G,
        VK_COMPONENT_SWIZZLE_B,
        VK_COMPONENT_SWIZZLE_A,
    };
    result = vkCreateImageView(mDevice->GetDevice(), &ivInfo, nullptr, &mImageView);
    RETURN_FALSE_IF_FAILED(result, "Failed to create Image View for Texture");

    LOGM("Created Texture (image " << std::hex << mImage << " view " << mImageView << " res " << std::dec << mWidth << "x" << mHeight << ")");
    return true;
}

bool Texture::AllocateDescriptorSet(VkDescriptorSetLayout layout, VkSampler sampler)
{
    mImageDescriptorSet = DescriptorAllocator::Instance().AllocateDescriptorSet(layout);
    if (mImageDescriptorSet == VK_NULL_HANDLE)
        return false;

    // TODO assumes image layout
    Tools::UpdateTextureDescriptorSet(mDevice, mImageDescriptorSet, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 0, this, sampler, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    return true;
}

} // namespace Renderer
} // namespace Krayo