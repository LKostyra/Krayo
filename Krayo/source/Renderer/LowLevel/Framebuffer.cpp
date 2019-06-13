#include "Renderer/LowLevel/Framebuffer.hpp"

#include "Renderer/LowLevel/Util.hpp"
#include "Renderer/LowLevel/Extensions.hpp"
#include "Renderer/HighLevel/Renderer.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Renderer {

Framebuffer::Framebuffer()
    : mFramebuffer(VK_NULL_HANDLE)
    , mWidth(0)
    , mHeight(0)
    , mTexturePtr(nullptr)
    , mDepthTexturePtr(nullptr)
{
}

Framebuffer::~Framebuffer()
{
    if (mFramebuffer != VK_NULL_HANDLE)
        vkDestroyFramebuffer(mDevice->GetDevice(), mFramebuffer, nullptr);
}

bool Framebuffer::Init(const DevicePtr& device, const FramebufferDesc& desc)
{
    mDevice = device;

    if (desc.colorTex && desc.depthTex)
    {
        if (((desc.colorTex->mWidth != desc.depthTex->mWidth) ||
             (desc.colorTex->mHeight != desc.depthTex->mHeight)))
        {
            LOGD("Color: " << desc.colorTex->mWidth << "x" << desc.colorTex->mHeight);
            LOGD("Depth: " << desc.depthTex->mWidth << "x" << desc.depthTex->mHeight);
            LOGE("Cannot create framebuffer - provided color and depth textures are incompatible");
            return false;
        }
    }

    if (desc.colorTex)
    {
        mWidth = desc.colorTex->mWidth;
        mHeight = desc.colorTex->mHeight;
    }
    else if (desc.depthTex)
    {
        mWidth = desc.depthTex->mWidth;
        mHeight = desc.depthTex->mHeight;
    }

    VkFramebufferCreateInfo fbInfo;
    LKCOMMON_ZERO_MEMORY(fbInfo);
    fbInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fbInfo.width = mWidth;
    fbInfo.height = mHeight;
    fbInfo.renderPass = desc.renderPass;
    fbInfo.layers = 1;

    VkImageView fbAtts[2];
    fbInfo.attachmentCount = 0;

    if (desc.colorTex)
    {
        fbAtts[fbInfo.attachmentCount] = desc.colorTex->mImageView;
        fbInfo.attachmentCount++;
    }

    if (desc.depthTex)
    {
        fbAtts[fbInfo.attachmentCount] = desc.depthTex->mImageView;
        fbInfo.attachmentCount++;
    }

    fbInfo.pAttachments = fbAtts;
    VkResult result = vkCreateFramebuffer(mDevice->GetDevice(), &fbInfo, nullptr, &mFramebuffer);
    RETURN_FALSE_IF_FAILED(result, "Failed to create Framebuffer");

    mTexturePtr = desc.colorTex;
    mDepthTexturePtr = desc.depthTex;

    return true;
}

} // namespace Renderer
} // namespace Krayo
