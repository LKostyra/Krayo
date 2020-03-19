#include "Krayo/Component/Model.hpp"

#include "Component/Model.hpp"
#include "Utils/Container.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Component {

Model::Model(const Component::ComponentID id)
    : IComponent(id)
{
    LOGD("Component ID: " << id);
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
