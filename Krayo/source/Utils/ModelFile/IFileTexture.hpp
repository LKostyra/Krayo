#pragma once


namespace Krayo {
namespace Utils {

class IFileTexture
{
public:
    virtual const void* GetBuffer() const = 0;
    virtual const void* GetBufferSize() const = 0;
};

} // namespace Utils
} // namespace Krayo

