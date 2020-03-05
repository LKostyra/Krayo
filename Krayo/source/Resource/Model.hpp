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
    std::shared_ptr<Internal::Material> material;
};

class Model: public ResourceBase<Model>
{
    friend class Component::Internal::Model;
    friend class Internal::Manager;

    using MeshContainer = std::vector<Mesh>;

    MeshContainer mMeshes;

public:
    Model(const std::string& name);

    bool Load(const std::shared_ptr<Utils::IFileData>& file) override; // load single mesh as a model
    bool Load(const std::unique_ptr<Utils::IModelFile>& file); // load all meshes as one model
};

} // namespace Internal
} // namespace Resource
} // namespace Krayo
