#pragma once

#include <lkCommon/lkCommon.hpp>
#include <lkCommon/Utils/Pixel.hpp>

#include "Resource.hpp"
#include "Texture.hpp"


namespace Krayo {
namespace Resources {

class Material: public Resource
{
    lkCommon::Utils::PixelFloat4 mColor;
    Resources::Texture* mDiffuse;
    Resources::Texture* mNormal;
    Resources::Texture* mMask;

public:
    Material(const std::string& name);

    bool Load(const std::string& path) override;

    LKCOMMON_INLINE ResourceType GetType() const
    {
        return ResourceType::Material;
    }

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

    LKCOMMON_INLINE void SetDiffuse(Resources::Texture* diffuse)
    {
        mDiffuse = diffuse;
    }

    LKCOMMON_INLINE void SetNormal(Resources::Texture* normal)
    {
        mNormal = normal;
    }

    LKCOMMON_INLINE void SetMask(Resources::Texture* mask)
    {
        mMask = mMask;
    }

    LKCOMMON_INLINE const Resources::Texture* GetDiffuse() const
    {
        return mDiffuse;
    }

    LKCOMMON_INLINE const Resources::Texture* GetNormal() const
    {
        return mNormal;
    }

    LKCOMMON_INLINE const Resources::Texture* GetMask() const
    {
        return mMask;
    }
};

} // namespace Resources
} // namespace Krayo
