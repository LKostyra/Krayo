#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include <memory>


namespace Krayo {
namespace Component {

using ComponentID = uint32_t;

class IComponent
{
protected:
    friend class Krayo::Map;
    friend class Krayo::Object;

    ComponentID mID;

    IComponent(const ComponentID id);

public:
    KRAYO_API virtual ~IComponent() = default;
};

} // namespace Component
} // namespace Krayo
