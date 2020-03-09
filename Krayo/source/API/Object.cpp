#include "Krayo/Object.hpp"

#include "Object.hpp"


namespace Krayo {

Object::Object(const std::shared_ptr<Internal::Object>& impl)
    : mImpl(impl)
{
}

void Object::AttachComponent(Component::IComponent& component)
{
    mImpl->AttachComponent(component.mImpl);
}

} // namespace Krayo
