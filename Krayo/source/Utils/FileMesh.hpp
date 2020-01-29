#pragma once

#include <lkCommon/Math/Vector2.hpp>
#include <lkCommon/Math/Vector3.hpp>

#include <vector>


namespace Krayo {
namespace Utils {

class FileMesh
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

public:
    LKCOMMON_INLINE void* GetVertexBufferData()
    {
        return mVertexBuffer.data();
    }

    LKCOMMON_INLINE size_t GetVertexBufferDataSize()
    {
        return mVertexBuffer.size() * sizeof(lkCommon::Math::Vector3);
    }

    LKCOMMON_INLINE void* GetVertexBufferParamsData()
    {
        return mVertexBufferParams.data();
    }

    LKCOMMON_INLINE size_t GetVertexBufferParamsDataSize()
    {
        return mVertexBufferParams.size() * sizeof(VertexBufferParams);
    }

    LKCOMMON_INLINE void* GetIndexBufferData()
    {
        return mIndexBuffer.data();
    }

    LKCOMMON_INLINE size_t GetIndexBufferDataSize()
    {
        return mIndexBuffer.size() * sizeof(uint32_t);
    }

    LKCOMMON_INLINE uint32_t GetPointCount()
    {
        return mPointCount;
    }
};

} // namespace Utils
} // namespace Krayo
