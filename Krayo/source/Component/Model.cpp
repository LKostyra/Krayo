#include "Model.hpp"

#include <lkCommon/lkCommon.hpp>
#include <lkCommon/Utils/Logger.hpp>

using namespace Krayo::Renderer;


namespace Krayo {
namespace Component {
namespace Internal {

Model::Model(const std::string& name)
    : IComponent(name)
    , mTransform()
    , mPosition(0.0f)
    , mScale(1.0f)
    , mMeshes()
    , mAABB()
    , mToRender(false)
{
}

bool Model::Init()
{
    // avoid reallocation - it could free our buffers
    /*mMeshes.reserve(modelDesc.materials.size());

    for (size_t i = 0; i < modelDesc.materials.size(); ++i)
    {
        mMeshes.emplace_back();
        Mesh& m = mMeshes.back();
        if (!m.Init())
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
    else*/

    mMeshes.reserve(1);
    mMeshes.emplace_back();
    Mesh& m = mMeshes.back();
    if (!m.Init())
    {
        LOGE("Failed to create mesh for model " << mName);
        return false;
    }

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

} // namespace Internal
} // namespace Component
} // namespace Krayo
