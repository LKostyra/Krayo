#pragma once

#include "Component/IComponent.hpp"

#include <string>


namespace Krayo {
namespace Scene {
namespace Internal {

class Object
{
    std::string mName;
    Component::Internal::IComponent* mComponent;

public:
    Object(const std::string& name);
    ~Object();

    void SetComponent(Component::Internal::IComponent* component)
    {
        mComponent = component;
    }

    Component::Internal::IComponent* GetComponent() const
    {
        return mComponent;
    }
};

} // namespace Internal
} // namespace Scene
} // namespace Krayo
