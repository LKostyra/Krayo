#pragma once

#include <lkCommon/lkCommon.hpp>

#include "Resource.hpp"
#include "Renderer/HighLevel/ResourceFactory.hpp"


namespace Krayo {
namespace Resources {

class Texture: public Resource
{
    Renderer::TexturePtr mRendererTexture;

    bool CreateRendererTexture(const std::string& imagePath, VkImageUsageFlags usage, Renderer::TexturePtr& texture);

public:
    Texture(const std::string& name);

    bool Load(const std::string& path) override;

    LKCOMMON_INLINE ResourceType GetType() const
    {
        return ResourceType::Texture;
    }
};

} // namespace Resources
} // namespace Krayo
