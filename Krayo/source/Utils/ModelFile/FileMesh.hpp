#pragma once

#include "IFileData.hpp"
#include "FileMaterial.hpp"

#include <lkCommon/Math/Vector2.hpp>
#include <lkCommon/Math/Vector3.hpp>

#include <vector>


namespace Krayo {
namespace Utils {

class FileMesh: public IFileData
{
    friend class IModelFile;
    friend class FBXModelFile;
    friend class KrayoJSONModelFile;
    friend class OBJModelFile;

    struct VertexBufferParams
    {
        lkCommon::Math::Vector3 normal;
        lkCommon::Math::Vector2 uv;
        lkCommon::Math::Vector3 tangent;
    };

    std::vector<lkCommon::Math::Vector3> mVertexBuffer;
    std::vector<VertexBufferParams> mVertexBufferParams;
    std::vector<uint32_t> mIndexBuffer;
    uint32_t mPointCount;
    std::string mMaterialName;

public:
    LKCOMMON_INLINE FileDataType GetType() const override
    {
        return FileDataType::Mesh;
    }

    LKCOMMON_INLINE const void* GetVertexBufferData() const
    {
        return mVertexBuffer.data();
    }

    LKCOMMON_INLINE size_t GetVertexBufferDataSize() const
    {
        return mVertexBuffer.size() * sizeof(lkCommon::Math::Vector3);
    }

    LKCOMMON_INLINE const void* GetVertexBufferParamsData() const
    {
        return mVertexBufferParams.data();
    }

    LKCOMMON_INLINE size_t GetVertexBufferParamsDataSize() const
    {
        return mVertexBufferParams.size() * sizeof(VertexBufferParams);
    }

    LKCOMMON_INLINE const void* GetIndexBufferData() const
    {
        return mIndexBuffer.data();
    }

    LKCOMMON_INLINE size_t GetIndexBufferDataSize() const
    {
        return mIndexBuffer.size() * sizeof(uint32_t);
    }

    LKCOMMON_INLINE uint32_t GetPointCount() const
    {
        return mPointCount;
    }

    LKCOMMON_INLINE const std::string& GetMaterialName() const
    {
        return mMaterialName;
    }
};

} // namespace Utils
} // namespace Krayo
