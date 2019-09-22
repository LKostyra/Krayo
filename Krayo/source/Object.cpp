#include "Object.hpp"

#include "Krayo/Object.hpp"
#include "Utils/TypeID.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Internal {

Object::Object(const std::string& name)
    : mName(name)
    , mComponents(Krayo::Utils::TypeID<Component::Internal::IComponent>::Count())
{
}

void Object::AttachComponent(Component::Internal::IComponent* component)
{
    mComponents[component->GetTypeID()] = component;
    LOGD("Attached component " << reinterpret_cast<void*>(component) <<
         " as type " << component->GetTypeID());
}

} // namespace Internal
} // namespace Krayo

