#pragma once

#include "IFileTexture.hpp"

#include <lkCommon/Utils/Image.hpp>


namespace Krayo {
namespace Utils {

class FileTextureSDR: public IFileTexture
{
    lkCommon::Utils::Image<lkCommon::Utils::PixelUint4> mImage;

public:
    LKCOMMON_INLINE FileDataType GetType() const override
    {
        return FileDataType::TextureSDR;
    }
};

} // namespace Utils
} // namespace Krayo

