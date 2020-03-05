#pragma once

#include <lkCommon/lkCommon.hpp>
#include <string>


namespace Krayo {
namespace Utils {

enum FileDataType
{
    Mesh,
    Texture,
    Material,
    TextureSDR,
    TextureHDR,
};

class IFileData
{
protected:
    std::string mName;

public:
    LKCOMMON_INLINE virtual FileDataType GetType() const = 0;

    LKCOMMON_INLINE const std::string& GetName() const
    {
        return mName;
    }
};

} // namespace Krayo
} // namespace Utils
