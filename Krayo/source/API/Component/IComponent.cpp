#include "Krayo/Component/IComponent.hpp"


namespace Krayo {
namespace Component {

IComponent::IComponent(const std::shared_ptr<Internal::IComponent>& impl)
    : mImpl(impl)
{
}

} // namespace Component
} // namespace Krayo
