#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/Component.hpp"


namespace Krayo {

class Object final
{
    std::string mName;
    Component* mComponent;

public:
    KRAYO_API Object(const std::string& name);
    KRAYO_API virtual ~Object() = default;

    KRAYO_INLINE void SetComponent(Component* component)
    {
        mComponent = component;
    }

    KRAYO_INLINE Component* GetComponent() const
    {
        return mComponent;
    }
};

} // namespace Krayo
