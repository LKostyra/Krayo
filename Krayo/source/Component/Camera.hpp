#pragma once

#include "Component/IComponent.hpp"

#include <lkCommon/Math/Matrix4.hpp>


namespace Krayo {
namespace Component {
namespace Internal {

class Camera: public ComponentBase<Camera>
{
    lkCommon::Math::Matrix4 mView;

public:
    Camera(const std::string& name);
};

} // namespace Internal
} // namespace Component
} // namespace Krayo
