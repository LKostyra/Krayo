#pragma once

#include "Scene/Object.hpp"
#include "Resource/Material.hpp"
#include "Math/AABB.hpp"


namespace Krayo {
namespace Scene {
namespace Internal {

struct Vertex
{
    float pos[3];
};

struct VertexParams
{
    float norm[3];
    float uv[2];
    float tang[3];
};

class Mesh final
{
    Krayo::Renderer::BufferPtr mVertexBuffer;
    Krayo::Renderer::BufferPtr mVertexParamsBuffer;
    Krayo::Renderer::BufferPtr mIndexBuffer;
    uint32_t mPointCount;
    Resource::Internal::Material* mMaterial;
    bool mByIndices;

    bool InitBuffers(const std::vector<Vertex>& vertices,
                     const std::vector<VertexParams>& vertexParams,
                     int* indices, int indexCount);
    bool InitDefault();

public:
    Mesh();
    ~Mesh();

    bool Init();

    LKCOMMON_INLINE void SetMaterial(Krayo::Resource::Internal::Material* mat)
    {
        mMaterial = mat;
    }

    LKCOMMON_INLINE const Krayo::Renderer::Buffer* GetVertexBuffer() const
    {
        return mVertexBuffer.get();
    }

    LKCOMMON_INLINE const Krayo::Renderer::Buffer* GetVertexParamsBuffer() const
    {
        return mVertexParamsBuffer.get();
    }

    LKCOMMON_INLINE const Krayo::Renderer::Buffer* GetIndexBuffer() const
    {
        return mIndexBuffer.get();
    }

    LKCOMMON_INLINE const uint32_t GetPointCount() const
    {
        return mPointCount;
    }

    LKCOMMON_INLINE const Krayo::Resource::Internal::Material* GetMaterial() const
    {
        return mMaterial;
    }

    LKCOMMON_INLINE bool ByIndices() const
    {
        return mByIndices;
    }
};

} // namespace Internal
} // namespace Scene
} // namespace Krayo
