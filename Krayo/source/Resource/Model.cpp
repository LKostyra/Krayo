#include "Model.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Resource {
namespace Internal {

Model::Model(const std::string& name)
    : ResourceBase<Model>(name)
{
}

bool Model::Load(const std::string& path)
{
    Utils::ModelFile* file = Utils::ModelLoader::Open(path);

    if (file == nullptr)
    {
        LOGE("Failed to load Model from file");
        return false;
    }

    return true;
}

bool Model::LoadMesh(const std::vector<float>& vertices)
{
    LOGD("Loading from Vertices");

    Renderer::BufferDesc vbDesc;
    LKCOMMON_ZERO_MEMORY(vbDesc);
    vbDesc.type = Renderer::BufferType::Static;
    vbDesc.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    vbDesc.data = vertices.data();
    vbDesc.dataSize = vertices.size() * sizeof(float);
    vbDesc.concurrent = false;
    /*
    mVertexBuffer = Renderer::ResourceFactory::Instance().CreateBuffer(vbDesc);
    if (!mVertexBuffer)
        return false;
        */
    return true;
}

} // namespace Internal
} // namespace Resource
} // namespace Krayo
