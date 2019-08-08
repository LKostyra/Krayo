#pragma once

#include <lkCommon/Utils/Pixel.hpp>

#include "Renderer/HighLevel/ResourceFactory.hpp"


namespace Krayo {
namespace Scene {

class Material
{
    friend class Mesh;

    std::string mMaterialName;

    lkCommon::Utils::PixelFloat4 mColor;
    Renderer::TexturePtr mDiffuseTexture;
    Renderer::TexturePtr mNormalTexture;
    Renderer::TexturePtr mMaskTexture;

    bool CreateRendererTexture(const std::string& image, VkImageUsageFlags usage, Renderer::TexturePtr& texture);

public:
    Material(const std::string& name);
    ~Material();

    LKCOMMON_INLINE void SetColor(float R, float G, float B)
    {
        mColor[0] = R;
        mColor[1] = G;
        mColor[2] = B;
    }

    LKCOMMON_INLINE const lkCommon::Utils::PixelFloat4& GetColor() const
    {
        return mColor;
    }

    LKCOMMON_INLINE const Renderer::TexturePtr& GetDiffuse() const
    {
        return mDiffuseTexture;
    }

    LKCOMMON_INLINE const Renderer::TexturePtr& GetNormal() const
    {
        return mNormalTexture;
    }

    LKCOMMON_INLINE const Renderer::TexturePtr& GetMask() const
    {
        return mMaskTexture;
    }
};

} // namespace Scene
} // namespace Krayo
