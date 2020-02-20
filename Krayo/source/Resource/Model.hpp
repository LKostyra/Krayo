#pragma once

#include "Krayo/Resource/Model.hpp"
#include "Resource/IResource.hpp"

#include "Utils/ModelLoader.hpp"

#include "Renderer/HighLevel/ResourceFactory.hpp"

#include <vector>
#include <functional>


namespace Krayo {
namespace Resource {
namespace Internal {

struct Mesh
{
    Renderer::BufferPtr vertexBuffer;
    Renderer::BufferPtr vertexParamsBuffer;
    Renderer::BufferPtr indexBuffer;
    uint32_t pointCount;
    bool byIndices;
};

class Model: public ResourceBase<Model>
{
    friend class Component::Internal::Model;

    using MeshContainer = std::vector<Mesh>;

    MeshContainer mMeshes;

public:
    Model(const std::string& name);

    bool Load(const std::unique_ptr<Utils::IModelFile>& file) override;
};

} // namespace Internal
} // namespace Resource
} // namespace Krayo
