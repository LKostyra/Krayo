#pragma once

#include "IFileData.hpp"
#include "IFileTexture.hpp"

#include <lkCommon/Utils/Pixel.hpp>
#include <memory>


namespace Krayo {
namespace Utils {

class FileMaterial: public IFileData
{
    friend class IModelFile;
    friend class FBXModelFile;
    friend class KrayoJSONModelFile;
    friend class OBJModelFile;

    lkCommon::Utils::PixelFloat4 mColor;
    std::shared_ptr<IFileTexture> mDiffuse;

public:
    LKCOMMON_INLINE FileDataType GetType() const override
    {
        return FileDataType::Material;
    }

    LKCOMMON_INLINE const lkCommon::Utils::PixelFloat4& GetColor() const
    {
        return mColor;
    }

    LKCOMMON_INLINE const std::shared_ptr<IFileTexture>& GetDiffuse() const
    {
        return mDiffuse;
    }
};

} // namespace Utils
} // namespace Krayo
