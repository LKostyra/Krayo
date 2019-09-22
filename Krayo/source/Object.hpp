#pragma once

#include <string>
#include <vector>

#include "Component/IComponent.hpp"


namespace Krayo {
namespace Internal {

class Object final
{
    std::string mName;

    std::vector<Component::Internal::IComponent*> mComponents;

public:
    Object(const std::string& name);
    ~Object() = default;

    void AttachComponent(Component::Internal::IComponent* component);
};

} // namespace Internal
} // namespace Krayo
