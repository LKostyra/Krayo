#pragma once

#include <lkCommon/lkCommon.hpp>

#include "IResource.hpp"

#include "Renderer/HighLevel/ResourceFactory.hpp"


namespace Krayo {
namespace Resource {
namespace Internal {

class Texture: public IResource
{
    Renderer::TexturePtr mRendererTexture;

    bool CreateRendererTexture(const std::string& imagePath, VkImageUsageFlags usage, Renderer::TexturePtr& texture);

public:
    Texture(const std::string& name);

    bool Load(const std::string& path) override;

    LKCOMMON_INLINE Krayo::Resource::Type GetType() const
    {
        return Krayo::Resource::Type::Texture;
    }
};

} // namespace Internal
} // namespace Resources
} // namespace Krayo
