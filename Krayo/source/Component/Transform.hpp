#pragma once

#include "Component/IComponent.hpp"


namespace Krayo {
namespace Component {
namespace Internal {

class Transform: public ComponentBase<Transform>
{
public:
    Transform(const std::string& name);
};

} // namespace Internal
} // namespace Component
} // namespace Krayo
