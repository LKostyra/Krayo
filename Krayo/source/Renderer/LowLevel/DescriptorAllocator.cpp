#include "Renderer/LowLevel/DescriptorAllocator.hpp"

#include "Renderer/LowLevel/Util.hpp"
#include "Renderer/LowLevel/Extensions.hpp"
#include "Renderer/LowLevel/Device.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Renderer {

DescriptorAllocator::DescriptorAllocator()
    : mMaxSets(0)
    , mLimits()
    , mPoolSizes()
    , mDescriptorPools()
{
}

DescriptorAllocator::~DescriptorAllocator()
{
    Release();
}

bool DescriptorAllocator::AllocateNewPool()
{
    mDescriptorPools.emplace_back();

    VkDescriptorPoolCreateInfo info;
    LKCOMMON_ZERO_MEMORY(info);
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    info.poolSizeCount = static_cast<uint32_t>(mPoolSizes.size());
    info.pPoolSizes = mPoolSizes.data();
    info.maxSets = mMaxSets;
    VkResult result = vkCreateDescriptorPool(mDevice->GetDevice(), &info, nullptr, &mDescriptorPools.back().pool);
    RETURN_NULL_HANDLE_IF_FAILED(result, "Failed to create Descriptor Pool");

    LOGD("Created Descriptor Pool 0x" << std::hex << reinterpret_cast<size_t*>(mDescriptorPools.back().pool));

    for (uint32_t i = 0; i < VK_DESCRIPTOR_TYPE_RANGE_SIZE; ++i)
    {
        mDescriptorPools.back().limits[i] = mLimits.limits[i];
        mDescriptorPools.back().taken[i] = 0;
    }

    return true;
}

DescriptorAllocator& DescriptorAllocator::Instance()
{
    static DescriptorAllocator instance;
    return instance;
}

bool DescriptorAllocator::Init(const DevicePtr& device, const DescriptorAllocatorDesc& desc)
{
    mDevice = device;

    VkDescriptorPoolSize size;
    for (uint32_t i = 0; i < VK_DESCRIPTOR_TYPE_RANGE_SIZE; ++i)
    {
        if (desc.limits[i] > 0)
        {
            mLimits.limits[i] = desc.limits[i];

            mMaxSets += mLimits.limits[i];
            size.descriptorCount = mLimits.limits[i];
            size.type = static_cast<VkDescriptorType>(i);
            mPoolSizes.push_back(size);
        }
    }

    // TODO check if we do not exceed device's limits
    return AllocateNewPool();
}

void DescriptorAllocator::Release()
{
    for (auto& p: mDescriptorPools)
        vkDestroyDescriptorPool(mDevice->GetDevice(), p.pool, nullptr);

    mDescriptorPools.clear();
    mDevice.reset();
}

VkDescriptorSet DescriptorAllocator::AllocateDescriptorSet(const VkDescriptorSetLayout layout)
{
    // TODO memory tracking (somehow)

    VkDescriptorSet set = VK_NULL_HANDLE;

    VkDescriptorSetAllocateInfo info;
    LKCOMMON_ZERO_MEMORY(info);
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    info.descriptorPool = mDescriptorPools.back().pool;
    info.descriptorSetCount = 1;
    info.pSetLayouts = &layout;
    VkResult result = vkAllocateDescriptorSets(mDevice->GetDevice(), &info, &set);
    // TODO add new pool if limits are exceeded
    RETURN_NULL_HANDLE_IF_FAILED(result, "Failed to allocate Descriptor Set");

    return set;
}

} // namespace Renderer
} // namespace Krayo
