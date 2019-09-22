#include "IComponent.hpp"


namespace Krayo {
namespace Component {
namespace Internal {

IComponent::IComponent(const std::string& name)
    : mName(name)
{
}

IComponent::~IComponent()
{
}

} // namespace Internal
} // namespace Component
} // namespace Krayo
