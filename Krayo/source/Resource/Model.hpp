#pragma once

#include "Krayo/Resource/Model.hpp"
#include "Resource/IResource.hpp"

#include "Utils/ModelLoader.hpp"

#include "Renderer/HighLevel/ResourceFactory.hpp"

#include <vector>


namespace Krayo {
namespace Resource {
namespace Internal {

class Model: public ResourceBase<Model>
{
    Renderer::BufferPtr mVertexBuffer;
    Renderer::BufferPtr mIndexBuffer;

public:
    Model(const std::string& name);

    bool Load(const std::string& path);
    bool LoadMesh(const std::vector<float>& vertices);
};

} // namespace Internal
} // namespace Resource
} // namespace Krayo
