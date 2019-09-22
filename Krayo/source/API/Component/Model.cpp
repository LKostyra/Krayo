#include "Krayo/Component/Model.hpp"

#include "Component/Model.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Component {

Model::Model(Internal::Model* impl)
    : IComponent(impl)
{
    LOGD("Model's Component ID: " << impl->GetTypeID());
}

Model::~Model()
{
}

void Model::AttachResource(Resource::Model* modelRes)
{
    dynamic_cast<Component::Internal::Model*>(mImpl)->AttachResource(
        dynamic_cast<Resource::Internal::Model*>(modelRes->mImpl)
    );
}

} // namespace Component
} // namespace Krayo
