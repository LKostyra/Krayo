#include "TypeID.hpp"

#include "Component/IComponent.hpp"
#include "Resource/IResource.hpp"


namespace Krayo {
namespace Utils {

template <>
uint32_t TypeID<Component::Internal::IComponent>::mCounter = 0;

template <>
uint32_t TypeID<Resource::Internal::IResource>::mCounter = 0;

} // namespace Krayo
} // namespace Utils
