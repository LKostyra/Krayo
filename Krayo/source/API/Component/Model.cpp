#include "Krayo/Component/Model.hpp"

#include "Component/Model.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Component {

Model::Model(const std::shared_ptr<Internal::Model>& impl)
    : IComponent(impl)
{
    LOGD("Model's Component ID: " << impl->GetTypeID());
}

Model::~Model()
{
}

void Model::AttachResource(Resource::Model modelRes)
{
    std::dynamic_pointer_cast<Internal::Model>(mImpl)->AttachResource(
        std::dynamic_pointer_cast<Resource::Internal::Model>(modelRes.mImpl)
    );
}

} // namespace Component
} // namespace Krayo
