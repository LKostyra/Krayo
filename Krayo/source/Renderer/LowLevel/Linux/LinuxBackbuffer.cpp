#include "Renderer/LowLevel/Linux/LinuxBackbuffer.hpp"

#include "Renderer/LowLevel/Backbuffer.hpp"
#include "Renderer/LowLevel/Extensions.hpp"
#include "Renderer/LowLevel/Util.hpp"

#include <vulkan/vulkan.h>

#include <lkCommon/lkCommon.hpp>
#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Renderer {

bool Backbuffer::CreateSurface(const BackbufferDesc& desc)
{
    VkXcbSurfaceCreateInfoKHR info;
    LKCOMMON_ZERO_MEMORY(info);
    info.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    info.connection = desc.windowDesc.connection;
    info.window = desc.windowDesc.window;
    VkResult result = vkCreateXcbSurfaceKHR(mInstance->GetVkInstance(), &info, nullptr, &mSurface);
    RETURN_FALSE_IF_FAILED(result, "Failed to create Vulkan Surface for XCB");

    return true;
}

} // namespace Renderer
} // namespace ABench
