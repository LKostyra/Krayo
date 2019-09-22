#include "Krayo/Component/Transform.hpp"

#include "Component/Transform.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Component {

Transform::Transform(Internal::Transform* impl)
    : IComponent(impl)
{
    LOGD("Transform's Component ID: " << impl->GetTypeID());
}

Transform::~Transform()
{
}

} // namespace Component
} // namespace Krayo
