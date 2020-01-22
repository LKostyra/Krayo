#pragma once

#include <lkCommon/lkCommon.hpp>


namespace Krayo {
namespace Utils {

enum class ModelFileType: unsigned char
{
    Unknown = 0,
    FBX,
    OBJ
};

class IModelFile
{
public:
    virtual ~IModelFile() {};

    virtual bool Open(const std::string& path) = 0;
    virtual LKCOMMON_INLINE ModelFileType GetType() const = 0;
};


} // namespace Utils
} // namespace Krayo
