#pragma once

#include "Renderer/LowLevel/Types.hpp"

#include <vulkan/vulkan.h>

#include <lkCommon/lkCommon.hpp>

#include <vector>
#include <array>


namespace Krayo {
namespace Renderer {

// The manager for queues possible to acquire from VkPhysicalDevice.
// Gives Device class access to available queues and determines whether
// hardware supports Asynchronous Compute.
class QueueManager
{
public:
    using QueueCreateInfos = std::vector<VkDeviceQueueCreateInfo>;

private:
    static const uint32_t INVALID_QUEUE_INDEX;

    struct DeviceQueue
    {
        uint32_t index;
        VkQueue queue;
        VkCommandPool commandPool;

        DeviceQueue()
            : index(INVALID_QUEUE_INDEX)
            , queue(VK_NULL_HANDLE)
            , commandPool(VK_NULL_HANDLE)
        {
        }
    };

    using QueueFamilyProperties = std::vector<VkQueueFamilyProperties>;
    using DeviceQueues = std::array<DeviceQueue, DeviceQueueType::COUNT>;

    VkDevice mDevice;
    QueueFamilyProperties mQueueProperties;
    QueueCreateInfos mQueueCreateInfos;
    DeviceQueues mQueues;
    std::array<float, 1> mQueuePriorities;
    std::vector<uint32_t> mQueueIndices;
    bool mSeparateTransferQueue;
    bool mSeparateComputeQueue;

    uint32_t GetQueueIndex(VkQueueFlags requestedFlag);

public:
    QueueManager();
    ~QueueManager();

    bool Init(VkPhysicalDevice physicalDevice, bool allowSeparateQueues);
    bool CreateQueues(VkDevice device);
    void Release();

    LKCOMMON_INLINE const QueueCreateInfos& GetQueueCreateInfos() const
    {
        return mQueueCreateInfos;
    }

    LKCOMMON_INLINE VkQueue GetQueue(DeviceQueueType queueType) const
    {
        return mQueues[queueType].queue;
    }

    LKCOMMON_INLINE VkCommandPool GetCommandPool(DeviceQueueType queueType) const
    {
        return mQueues[queueType].commandPool;
    }

    LKCOMMON_INLINE uint32_t GetQueueIndex(DeviceQueueType queueType) const
    {
        return mQueues[queueType].index;
    }

    LKCOMMON_INLINE uint32_t GetQueueCount() const
    {
        return static_cast<uint32_t>(mQueueIndices.size());
    }

    LKCOMMON_INLINE const uint32_t* GetQueueIndices() const
    {
        return mQueueIndices.data();
    }
};

} // namespace Krayo
} // namespace Renderer
