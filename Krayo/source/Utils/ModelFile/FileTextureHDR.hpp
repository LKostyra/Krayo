#pragma once

#include "IFileTexture.hpp"

#include <lkCommon/Utils/Image.hpp>


namespace Krayo {
namespace Utils {

class FileTextureHDR: public IFileTexture
{
    lkCommon::Utils::Image<lkCommon::Utils::PixelFloat4> mImage;

public:

};

} // namespace Utils
} // namespace Krayo

