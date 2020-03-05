#pragma once

#include <lkCommon/lkCommon.hpp>

#include "FileMesh.hpp"
#include "FileMaterial.hpp"
#include "IFileTexture.hpp"


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
public:
    template<typename T>
    using ResourceContainer = std::vector<std::shared_ptr<T>>;

protected:
    std::string mName;
    ResourceContainer<FileMesh> mMeshes;
    ResourceContainer<FileMaterial> mMaterials;
    ResourceContainer<IFileTexture> mTextures;

public:
    virtual ~IModelFile() {};

    virtual bool Open(const std::string& path) = 0;
    virtual LKCOMMON_INLINE ModelFileType GetType() const = 0;

    LKCOMMON_INLINE const std::string& GetName() const
    {
        return mName;
    }

    LKCOMMON_INLINE const ResourceContainer<FileMesh>& GetMeshes() const
    {
        return mMeshes;
    }

    LKCOMMON_INLINE const ResourceContainer<FileMaterial>& GetMaterials() const
    {
        return mMaterials;
    }

    LKCOMMON_INLINE const ResourceContainer<IFileTexture>& GetTextures() const
    {
        return mTextures;
    }
};


} // namespace Utils
} // namespace Krayo
