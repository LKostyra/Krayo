#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"


namespace Krayo {
namespace Component {

class IComponent
{
protected:
    friend class Krayo::Map;
    friend class Krayo::Object;

    Internal::IComponent* mImpl;

    IComponent(Internal::IComponent* impl);

public:
    KRAYO_API virtual ~IComponent() = default;
};

} // namespace Component
} // namespace Krayo
