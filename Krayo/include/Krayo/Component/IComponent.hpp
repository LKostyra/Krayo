#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include <memory>


namespace Krayo {
namespace Component {

class IComponent
{
protected:
    friend class Krayo::Map;
    friend class Krayo::Object;

    std::shared_ptr<Internal::IComponent> mImpl;

    IComponent(const std::shared_ptr<Internal::IComponent>& impl);

public:
    KRAYO_API virtual ~IComponent() = default;
};

} // namespace Component
} // namespace Krayo
