#pragma once

#include <lkCommon/lkCommon.hpp>

#include "Utils/FileMesh.hpp"


namespace Krayo {
namespace Utils {

enum class ModelFileType: unsigned char
{
    Unknown = 0,
    FBX,
    OBJ,
    KrayoJSON,
};

class IModelFile
{
protected:
    std::string mName;
    std::vector<FileMesh> mMeshes;

public:
    virtual ~IModelFile() {};

    virtual bool Open(const std::string& path) = 0;
    virtual uint32_t GetMeshCount() const = 0;
    virtual LKCOMMON_INLINE ModelFileType GetType() const = 0;

    LKCOMMON_INLINE const std::string& GetName() const
    {
        return mName;
    }

    LKCOMMON_INLINE FileMesh& GetMesh(uint32_t i)
    {
        return mMeshes[i];
    }
};


} // namespace Utils
} // namespace Krayo
