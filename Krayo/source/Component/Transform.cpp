#include "Transform.hpp"



namespace Krayo {
namespace Component {
namespace Internal {

Transform::Transform(const std::string& name)
    : ComponentBase<Transform>(name)
    , mTransform(lkCommon::Math::Matrix4::IDENTITY)
{
}

} // namespace Internal
} // namespace Component
} // namespace Krayo
