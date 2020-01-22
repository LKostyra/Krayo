#include "Renderer/LowLevel/Buffer.hpp"

#include "Renderer/LowLevel/Util.hpp"
#include "Renderer/LowLevel/Extensions.hpp"
#include "Renderer/LowLevel/CommandBuffer.hpp"
#include "Renderer/HighLevel/Renderer.hpp"


namespace Krayo {
namespace Renderer {

Buffer::Buffer()
    : mDevice()
    , mType(BufferType::Static)
    , mBuffer(VK_NULL_HANDLE)
    , mBufferMemory(VK_NULL_HANDLE)
    , mBufferSize(0)
{
}

Buffer::~Buffer()
{
    Free();
}

bool Buffer::Init(const DevicePtr& device, const BufferDesc& desc)
{
    mDevice = device;

    if ((desc.type == BufferType::Static) && (!desc.data || desc.dataSize == 0))
    {
        LOGE("Invalid/empty data provided for Static Buffer initialization");
        return false;
    }

    VkDeviceMemory stagingMemory = VK_NULL_HANDLE;
    VkBuffer staging = VK_NULL_HANDLE;

    mBufferSize = desc.dataSize;

    // create our buffer
    VkBufferCreateInfo bufInfo;
    LKCOMMON_ZERO_MEMORY(bufInfo);
    bufInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufInfo.size = mBufferSize;
    bufInfo.usage = desc.usage | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    bufInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if (desc.concurrent && device->GetQueueCount() > 1)
    {
        bufInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
        bufInfo.queueFamilyIndexCount = device->GetQueueCount();
        bufInfo.pQueueFamilyIndices = device->GetQueueIndices();
    }
    VkResult result = vkCreateBuffer(mDevice->GetDevice(), &bufInfo, nullptr, &mBuffer);
    RETURN_FALSE_IF_FAILED(result, "Failed to create device buffer");

    VkMemoryRequirements deviceMemReqs;
    vkGetBufferMemoryRequirements(mDevice->GetDevice(), mBuffer, &deviceMemReqs);

    VkMemoryPropertyFlags memFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    if (desc.type == BufferType::Static)
        memFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

    VkMemoryAllocateInfo memInfo;
    LKCOMMON_ZERO_MEMORY(memInfo);
    memInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memInfo.allocationSize = deviceMemReqs.size;
    memInfo.memoryTypeIndex = mDevice->GetMemoryTypeIndex(deviceMemReqs.memoryTypeBits, memFlags);
    result = vkAllocateMemory(mDevice->GetDevice(), &memInfo, nullptr, &mBufferMemory);
    RETURN_FALSE_IF_FAILED(result, "Failed to allocate device memory");

    result = vkBindBufferMemory(mDevice->GetDevice(), mBuffer, mBufferMemory, 0);
    RETURN_FALSE_IF_FAILED(result, "Failed to bind device memory to device buffer");

    if (desc.data != nullptr)
    {
        // create a staging buffer for copy operations
        bufInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        result = vkCreateBuffer(mDevice->GetDevice(), &bufInfo, nullptr, &staging);
        RETURN_FALSE_IF_FAILED(result, "Failed to create staging buffer");

        // get staging buffer's memory requirements
        VkMemoryRequirements stagingMemReqs;
        vkGetBufferMemoryRequirements(mDevice->GetDevice(), staging, &stagingMemReqs);

        // allocate memory for staging buffer
        memInfo.allocationSize = stagingMemReqs.size;
        memInfo.memoryTypeIndex = mDevice->GetMemoryTypeIndex(stagingMemReqs.memoryTypeBits,
                                                              VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        result = vkAllocateMemory(mDevice->GetDevice(), &memInfo, nullptr, &stagingMemory);
        RETURN_FALSE_IF_FAILED(result, "Failed to allocate memory for staging buffer");

        // map the memory and copy data to it
        void* stagingData = nullptr;
        result = vkMapMemory(mDevice->GetDevice(), stagingMemory, 0, stagingMemReqs.size, 0, &stagingData);
        RETURN_FALSE_IF_FAILED(result, "Failed to map staging memory for copying");
        memcpy(stagingData, desc.data, static_cast<size_t>(desc.dataSize));
        vkUnmapMemory(mDevice->GetDevice(), stagingMemory);

        result = vkBindBufferMemory(mDevice->GetDevice(), staging, stagingMemory, 0);
        RETURN_FALSE_IF_FAILED(result, "Failed to bind staging memory to staging buffer");

        // copy data from staging buffer to device
        // TODO OPTIMIZE this uses graphics queue and waits; after implementing queue manager, switch to Transfer queue
        CommandBuffer copyCmdBuffer;
        if (!copyCmdBuffer.Init(mDevice, desc.ownerQueueFamily))
            return false;

        copyCmdBuffer.Begin();
        copyCmdBuffer.BufferBarrier(this,
                                    VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
                                    0, VK_ACCESS_TRANSFER_WRITE_BIT,
                                    VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED);
        copyCmdBuffer.CopyBuffer(staging, mBuffer, deviceMemReqs.size);
        copyCmdBuffer.BufferBarrier(this,
                                    VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                    VK_ACCESS_TRANSFER_WRITE_BIT, 0,
                                    VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED);
        copyCmdBuffer.End();

        // TODO call on Transfer queue
        mDevice->Execute(desc.ownerQueueFamily, &copyCmdBuffer);
        mDevice->Wait(desc.ownerQueueFamily); // TODO this should be removed

        // cleanup
        vkFreeMemory(mDevice->GetDevice(), stagingMemory, nullptr);
        vkDestroyBuffer(mDevice->GetDevice(), staging, nullptr);
    }
    else
    {
        // perform a simple touch on our buffer with a barrier
        // that way it's gonna be owned by whatever queue family we asked
        CommandBuffer touchCmdBuffer;
        if (!touchCmdBuffer.Init(mDevice, desc.ownerQueueFamily))
            return false;

        touchCmdBuffer.Begin();
        touchCmdBuffer.BufferBarrier(this,
                                     VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                     0, 0,
                                     VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED);
        touchCmdBuffer.End();

        // TODO call on Transfer queue
        mDevice->Execute(desc.ownerQueueFamily, &touchCmdBuffer);
        mDevice->Wait(desc.ownerQueueFamily); // TODO this should be removed
    }

    mType = desc.type;
    return true;
}

bool Buffer::Write(const void* data, size_t size, size_t offset)
{
    if (mType == BufferType::Static)
    {
        LOGE("Cannot write to static buffer.");
        return false;
    }

    if (offset + size > mBufferSize)
    {
        LOGE("Write operation extends buffer size (offset + size > bufferSize): " << offset + size << " > " << mBufferSize);
        return false;
    }

    void* memory;
    VkResult result = vkMapMemory(mDevice->GetDevice(), mBufferMemory, static_cast<VkDeviceSize>(offset),
                                  static_cast<VkDeviceSize>(size), 0, &memory);
    RETURN_FALSE_IF_FAILED(result, "Failed to map memory for writing");
    memcpy(memory, data, size);
    vkUnmapMemory(mDevice->GetDevice(), mBufferMemory);

    return true;
}

bool Buffer::Read(void* data, size_t size, size_t offset)
{
    if (mType == BufferType::Static)
    {
        LOGE("Cannot read from static buffer.");
        return false;
    }

    if (offset + size > mBufferSize)
    {
        LOGE("Read operation extends buffer size (offset + size > bufferSize): " << offset + size << " > " << mBufferSize);
        return false;
    }

    void* memory;
    VkResult result = vkMapMemory(mDevice->GetDevice(), mBufferMemory, static_cast<VkDeviceSize>(offset),
                                  static_cast<VkDeviceSize>(size), 0, &memory);
    RETURN_FALSE_IF_FAILED(result, "Failed to map memory for reading");
    memcpy(data, memory, size);
    vkUnmapMemory(mDevice->GetDevice(), mBufferMemory);

    return true;
}

void Buffer::Free()
{
    if (mBufferMemory != VK_NULL_HANDLE)
        vkFreeMemory(mDevice->GetDevice(), mBufferMemory, nullptr);
    if (mBuffer != VK_NULL_HANDLE)
        vkDestroyBuffer(mDevice->GetDevice(), mBuffer, nullptr);

    mBufferMemory = VK_NULL_HANDLE;
    mBuffer = VK_NULL_HANDLE;
}

void Buffer::Dump()
{
    LKCOMMON_ASSERT(mType == BufferType::Dynamic, "Only dynamic buffers can be dumped");

    void* ptr = nullptr;
    VkResult result = vkMapMemory(mDevice->GetDevice(), mBufferMemory, 0, mBufferSize, 0, &ptr);
    if (result != VK_SUCCESS)
    {
        LOGW("Failed to map buffer's memory for dump");
        return;
    }

    LOGD("Buffer " << std::hex << mBuffer << " memory address: " << ptr);
    LKCOMMON_ASSERT(false, "Memory dump forced program termination");

    vkUnmapMemory(mDevice->GetDevice(), mBufferMemory);
}

} // namespace Renderer
} // namespace Krayo
