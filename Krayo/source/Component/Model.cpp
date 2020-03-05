#include "Model.hpp"



namespace Krayo {
namespace Component {
namespace Internal {

Model::Model(const std::string& name)
    : ComponentBase<Model>(name)
{
}

void Model::AttachResource(const std::shared_ptr<Resource::Internal::Model>& modelRes)
{
    mModelResource = modelRes;
    LOGD("Attached resource " << reinterpret_cast<void*>(mModelResource.get()));
}

const std::shared_ptr<Resource::Internal::Model>& Model::GetResource() const
{
    return mModelResource;
}

void Model::ForEachMesh(const Callback<Resource::Internal::Mesh>& callback) const
{
    if (!mModelResource)
        return;

    for (const auto& m: mModelResource->mMeshes)
        if (!callback(&m))
            return;
}

} // namespace Internal
} // namespace Component
} // namespace Krayo
