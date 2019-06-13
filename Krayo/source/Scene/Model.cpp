#include "Scene/Model.hpp"

#include <lkCommon/lkCommon.hpp>
#include <lkCommon/Utils/Logger.hpp>

using namespace Krayo::Renderer;


namespace Krayo {
namespace Scene {

Model::Model(const std::string& name)
    : Component(name)
    , mTransform()
    , mPosition(0.0f)
    , mScale(1.0f)
    , mMeshes()
    , mAABB()
    , mToRender(false)
{
}

Model::~Model()
{
}

bool Model::Init(const ModelDesc& modelDesc)
{
    if (modelDesc.materials.size() == 0)
    {
        LOGE("A material is required to create a model");
        return false;
    }

    // avoid reallocation - it could free our buffers
    mMeshes.reserve(modelDesc.materials.size());

    for (size_t i = 0; i < modelDesc.materials.size(); ++i)
    {
        mMeshes.emplace_back();
        Mesh& m = mMeshes.back();
        if (!m.Init(modelDesc.mesh, static_cast<uint32_t>(i)))
        {
            LOGE("Failed to create mesh " << i << " for model " << mName);
            return false;
        }
        m.SetMaterial(modelDesc.materials[i]);
    }

    if (modelDesc.mesh)
    {
        // TODO simplify AABB by adding extra utils like "contains"
        modelDesc.mesh->ComputeBBox();
        lkCommon::Math::Vector4 minVert(static_cast<float>(modelDesc.mesh->BBoxMin.Get()[0]),
                                        static_cast<float>(modelDesc.mesh->BBoxMin.Get()[1]),
                                        static_cast<float>(modelDesc.mesh->BBoxMin.Get()[2]),
                                        1.0f);
        lkCommon::Math::Vector4 maxVert(static_cast<float>(modelDesc.mesh->BBoxMax.Get()[0]),
                                        static_cast<float>(modelDesc.mesh->BBoxMax.Get()[1]),
                                        static_cast<float>(modelDesc.mesh->BBoxMax.Get()[2]),
                                        1.0f);
        mAABB = Math::AABB(minVert, maxVert);
    }
    else
    {
        mAABB = Math::AABB(
            lkCommon::Math::Vector4(-0.5f, -0.5f, -0.5f, 1.0f),
            lkCommon::Math::Vector4(0.5f, 0.5f, 0.5f, 1.0f)
        );
    }

    return true;
}

void Model::ForEachMesh(MeshTraverseCallback callback)
{
    for (auto& m: mMeshes)
        callback(&m);
}

} // namespace Scene
} // namespace Krayo
