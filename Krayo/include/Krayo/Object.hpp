#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include "Krayo/Component/IComponent.hpp"


namespace Krayo {

class Object final
{
    friend class Krayo::Map;

    std::shared_ptr<Internal::Object> mImpl;

    Object(const std::shared_ptr<Internal::Object>& impl);

public:
    KRAYO_API ~Object() = default;

    KRAYO_API void AttachComponent(Component::IComponent& component);
};

} // namespace Krayo