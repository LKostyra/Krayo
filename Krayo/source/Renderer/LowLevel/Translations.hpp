#pragma once

#include <vulkan/vulkan.h>
#include "Types.hpp"

#include <string>


namespace Krayo {
namespace Renderer {

const char* TranslateDeviceQueueTypeToString(uint32_t queueType);
const char* TranslateVkDescriptorTypeToString(VkDescriptorType type);
uint32_t TranslateVkFormatToFormatSize(VkFormat format);
const char* TranslateVkFormatToString(VkFormat format);
const char* TranslateVkImageLayoutToString(VkImageLayout layout);
const char* TranslateVkPhysicalDeviceTypeToString(VkPhysicalDeviceType type);
const char* TranslateVkQueueFlagsToString(VkQueueFlags flags);
const char* TranslateVkResultToString(VkResult result);

} // namespace Renderer
} // namespace Krayo
