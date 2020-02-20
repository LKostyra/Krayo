#include "Model.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Resource {
namespace Internal {

Model::Model(const std::string& name)
    : ResourceBase<Model>(name)
    , mMeshes()
{
}

bool Model::Load(const std::unique_ptr<Utils::IModelFile>& file)
{
    size_t meshCount = file->GetMeshes().size();
    mMeshes.resize(meshCount);

    Renderer::ResourceFactory& factory = Renderer::ResourceFactory::Instance();
    for (size_t i = 0; i < meshCount; ++i)
    {
        Renderer::BufferDesc vbDesc;
        vbDesc.data = file->GetMeshes()[i].GetVertexBufferData();
        vbDesc.dataSize = file->GetMeshes()[i].GetVertexBufferDataSize();
        vbDesc.type = Renderer::BufferType::Static;
        vbDesc.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        vbDesc.concurrent = false;
        vbDesc.ownerQueueFamily = Renderer::DeviceQueueType::GRAPHICS;
        mMeshes[i].vertexBuffer = factory.CreateBuffer(vbDesc);

        Renderer::BufferDesc vbParamsDesc;
        vbParamsDesc.data = file->GetMeshes()[i].GetVertexBufferParamsData();
        vbParamsDesc.dataSize = file->GetMeshes()[i].GetVertexBufferParamsDataSize();
        vbParamsDesc.type = Renderer::BufferType::Static;
        vbParamsDesc.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        vbParamsDesc.concurrent = false;
        vbParamsDesc.ownerQueueFamily = Renderer::DeviceQueueType::GRAPHICS;
        mMeshes[i].vertexParamsBuffer = factory.CreateBuffer(vbParamsDesc);

        Renderer::BufferDesc ibDesc;
        ibDesc.data = file->GetMeshes()[i].GetIndexBufferData();
        ibDesc.dataSize = file->GetMeshes()[i].GetIndexBufferDataSize();
        ibDesc.type = Renderer::BufferType::Static;
        ibDesc.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        ibDesc.concurrent = false;
        ibDesc.ownerQueueFamily = Renderer::DeviceQueueType::GRAPHICS;
        mMeshes[i].indexBuffer = factory.CreateBuffer(ibDesc);

        mMeshes[i].byIndices = true;
        mMeshes[i].pointCount = file->GetMeshes()[i].GetPointCount();
    }

    return true;
}

} // namespace Internal
} // namespace Resource
} // namespace Krayo
