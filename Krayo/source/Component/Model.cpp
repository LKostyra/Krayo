#include "Model.hpp"



namespace Krayo {
namespace Component {
namespace Internal {

Model::Model(const std::string& name)
    : ComponentBase<Model>(name)
{
}

void Model::AttachResource(Resource::Internal::Model* modelRes)
{
    mModelResource = modelRes;
    LOGD("Attached resource " << reinterpret_cast<void*>(mModelResource));
}

Resource::Internal::Model* Model::GetResource() const
{
    return mModelResource;
}

} // namespace Internal
} // namespace Component
} // namespace Krayo
