#pragma once

#include "Krayo/ApiDef.hpp"

#include "Krayo/Component/Type.hpp"

#include <string>


namespace Krayo {
namespace Component {
namespace Internal {

class IComponent
{
protected:
    std::string mName;

public:
    IComponent(const std::string& name);

    virtual Krayo::Component::Type GetType() const = 0;

    KRAYO_INLINE std::string GetName() const
    {
        return mName;
    }
};

} // namespace Internal
} // namespace Component
} // namespace Krayo
