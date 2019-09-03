#pragma once

#include "Component.hpp"

#include <string>


namespace Krayo {
namespace Scene {
namespace Internal {

class Object
{
    std::string mName;
    Component* mComponent;

public:
    Object(const std::string& name);
    ~Object();

    void SetComponent(Component* component)
    {
        mComponent = component;
    }

    Component* GetComponent() const
    {
        return mComponent;
    }
};

} // namespace Internal
} // namespace Scene
} // namespace Krayo
