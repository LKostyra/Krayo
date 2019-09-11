#pragma once

#include "Krayo/ApiDef.hpp"

#include <string>


namespace Krayo {
namespace Component {
namespace Internal {

enum class Type: unsigned char
{
    Invalid = 0,
    Model,
    Light,
    Emitter,
};

class IComponent
{
protected:
    std::string mName;

public:
    IComponent(const std::string& name);

    virtual Type GetType() const = 0;

    KRAYO_INLINE std::string GetName() const
    {
        return mName;
    }
};

} // namespace Internal
} // namespace Component
} // namespace Krayo
