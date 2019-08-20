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

class ModelFile
{
public:
    virtual LKCOMMON_INLINE ModelFileType GetType() = 0;
};


} // namespace Utils
} // namespace Krayo
