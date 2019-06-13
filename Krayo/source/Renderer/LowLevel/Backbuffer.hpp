#pragma once

#include "Prerequisites.hpp"
#include "Renderer/LowLevel/Instance.hpp"
#include "Renderer/LowLevel/Device.hpp"
#include "Renderer/LowLevel/CommandBuffer.hpp"
#include "Renderer/LowLevel/Tools.hpp"

#ifdef WIN32
#include "Renderer/LowLevel/Win/WinBackbuffer.hpp"
#elif defined(__linux__) | defined(__LINUX__)
#include "Renderer/LowLevel/Linux/LinuxBackbuffer.hpp"
#else
#error "Target platform not supported."
#endif


namespace Krayo {
namespace Renderer {

struct BackbufferDesc
{
    InstancePtr instancePtr;

    BackbufferWindowDesc windowDesc;

    VkFormat requestedFormat;
    bool vsync;
    uint32_t bufferCount;
    uint32_t width;
    uint32_t height;

    BackbufferDesc()
        : requestedFormat(VK_FORMAT_UNDEFINED)
        , vsync(false)
        , bufferCount(2)
        , width(0)
        , height(0)
    {
    }
};

struct BackbufferImageData
{
    VkImage image;
    VkImageLayout layout;

    BackbufferImageData()
        : image(VK_NULL_HANDLE)
        , layout(VK_IMAGE_LAYOUT_UNDEFINED)
    {
    }
};

class Backbuffer
{
    friend class CommandBuffer;

    InstancePtr mInstance;
    DevicePtr mDevice;

    uint32_t mWidth;
    uint32_t mHeight;
    VkFormat mFormat;
    std::vector<BackbufferImageData> mImages;
    VkImageSubresourceRange mSubresourceRange;
    VkImageLayout mDefaultLayout;
    uint32_t mCurrentBuffer;

    VkSurfaceKHR mSurface;
    uint32_t mPresentQueueIndex;
    VkQueue mPresentQueue;
    VkColorSpaceKHR mColorSpace;
    VkPresentModeKHR mPresentMode;
    VkSurfaceCapabilitiesKHR mSurfCaps;
    VkSwapchainKHR mSwapchain;
    uint32_t mBufferCount;

    CommandBuffer mCopyCommandBuffer;
    VkRAII<VkSemaphore> mCopySemaphore;
    VkRAII<VkFence> mCopyFence;

    bool CreateSurface(const BackbufferDesc& desc);
    bool GetPresentQueue();
    bool SelectSurfaceFormat(const BackbufferDesc& desc);
    bool SelectPresentMode(const BackbufferDesc& desc);
    bool AcquireSurfaceCaps();
    void SelectBufferCount(const BackbufferDesc& desc);
    bool CreateSwapchain(const BackbufferDesc& desc);
    bool AllocateImageViews();

    void Transition(CommandBuffer* cmdBuffer, VkPipelineStageFlags fromStage, VkPipelineStageFlags toStage,
                    VkAccessFlags fromAccess, VkAccessFlags toAccess,
                    uint32_t fromQueueFamily, uint32_t toQueueFamily,
                    VkImageLayout targetLayout);

public:
    Backbuffer();
    ~Backbuffer();

    bool Init(const DevicePtr& device, const BackbufferDesc& desc);

    // Acquire new image. This should be called at the beginning of the frame.
    bool AcquireNextImage(VkSemaphore semaphore);

    // Present current image on screen. This should be usually called at the end of current frame.
    bool Present(Texture& texture, VkSemaphore waitSemaphore);

    LKCOMMON_INLINE uint32_t GetWidth() const
    {
        return mWidth;
    }

    LKCOMMON_INLINE uint32_t GetHeight() const
    {
        return mHeight;
    }

    LKCOMMON_INLINE VkFormat GetFormat() const
    {
        return mFormat;
    }
};

} // namespace Renderer
} // namespace Krayo
