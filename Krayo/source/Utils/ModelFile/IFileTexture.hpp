#pragma once

#include "IFileData.hpp"


namespace Krayo {
namespace Utils {

class IFileTexture: public IFileData
{
public:
    virtual const void* GetBuffer() const = 0;
    virtual size_t GetBufferSize() const = 0;

    LKCOMMON_INLINE FileDataType GetType() const override
    {
        return FileDataType::Texture;
    }
};

} // namespace Utils
} // namespace Krayo

