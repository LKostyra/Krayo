#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include "Krayo/Component/IComponent.hpp"


namespace Krayo {

class Object final
{
    friend class Krayo::Map;

    Internal::Object* mImpl;

    Object(Internal::Object* impl);

public:
    KRAYO_API ~Object() = default;

    KRAYO_API void AttachComponent(Component::IComponent* component);
};

} // namespace Krayo