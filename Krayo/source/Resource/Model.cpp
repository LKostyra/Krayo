#include "Model.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Resource {
namespace Internal {

Model::Model(const std::string& name)
    : ResourceBase<Model>(name)
    , mFile()
    , mMeshes()
{
}

bool Model::Load(const std::string& path)
{
    mFile = Utils::ModelLoader::Open(path);

    if (!mFile)
    {
        LOGE("Failed to load Model from file");
        return false;
    }

    uint32_t meshCount = mFile->GetMeshCount();
    mMeshes.resize(meshCount);

    Renderer::ResourceFactory& factory = Renderer::ResourceFactory::Instance();
    for (uint32_t i = 0; i < meshCount; ++i)
    {
        Renderer::BufferDesc vbDesc;
        vbDesc.data = mFile->GetMesh(i).GetVertexBufferData();
        vbDesc.dataSize = mFile->GetMesh(i).GetVertexBufferDataSize();
        vbDesc.type = Renderer::BufferType::Static;
        vbDesc.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        vbDesc.concurrent = false;
        vbDesc.ownerQueueFamily = Renderer::DeviceQueueType::GRAPHICS;
        mMeshes[i].vertexBuffer = factory.CreateBuffer(vbDesc);

        Renderer::BufferDesc vbParamsDesc;
        vbParamsDesc.data = mFile->GetMesh(i).GetVertexBufferParamsData();
        vbParamsDesc.dataSize = mFile->GetMesh(i).GetVertexBufferParamsDataSize();
        vbParamsDesc.type = Renderer::BufferType::Static;
        vbParamsDesc.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        vbParamsDesc.concurrent = false;
        vbParamsDesc.ownerQueueFamily = Renderer::DeviceQueueType::GRAPHICS;
        mMeshes[i].vertexParamsBuffer = factory.CreateBuffer(vbParamsDesc);

        Renderer::BufferDesc ibDesc;
        ibDesc.data = mFile->GetMesh(i).GetIndexBufferData();
        ibDesc.dataSize = mFile->GetMesh(i).GetIndexBufferDataSize();
        ibDesc.type = Renderer::BufferType::Static;
        ibDesc.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        ibDesc.concurrent = false;
        ibDesc.ownerQueueFamily = Renderer::DeviceQueueType::GRAPHICS;
        mMeshes[i].indexBuffer = factory.CreateBuffer(ibDesc);

        mMeshes[i].byIndices = true;
        mMeshes[i].pointCount = mFile->GetMesh(i).GetPointCount();
    }

    return true;
}

} // namespace Internal
} // namespace Resource
} // namespace Krayo
