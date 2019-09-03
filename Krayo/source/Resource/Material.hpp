#pragma once

#include <lkCommon/lkCommon.hpp>
#include <lkCommon/Utils/Pixel.hpp>

#include "IResource.hpp"
#include "Texture.hpp"


namespace Krayo {
namespace Resource {
namespace Internal {

class Material: public IResource
{
    lkCommon::Utils::PixelFloat4 mColor;
    Texture* mDiffuse;
    Texture* mNormal;
    Texture* mMask;

public:
    Material(const std::string& name);

    bool Load(const std::string& path) override;

    LKCOMMON_INLINE Krayo::Resource::Type GetType() const
    {
        return Krayo::Resource::Type::Material;
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

    LKCOMMON_INLINE void SetDiffuse(Texture* diffuse)
    {
        mDiffuse = diffuse;
    }

    LKCOMMON_INLINE void SetNormal(Texture* normal)
    {
        mNormal = normal;
    }

    LKCOMMON_INLINE void SetMask(Texture* mask)
    {
        mMask = mMask;
    }

    LKCOMMON_INLINE const Texture* GetDiffuse() const
    {
        return mDiffuse;
    }

    LKCOMMON_INLINE const Texture* GetNormal() const
    {
        return mNormal;
    }

    LKCOMMON_INLINE const Texture* GetMask() const
    {
        return mMask;
    }
};

} // namespace Internal
} // namespace Resource
} // namespace Krayo
