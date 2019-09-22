#include "Krayo/Component/IComponent.hpp"


namespace Krayo {
namespace Component {

IComponent::IComponent(Internal::IComponent* impl)
    : mImpl(impl)
{
}

} // namespace Component
} // namespace Krayo
