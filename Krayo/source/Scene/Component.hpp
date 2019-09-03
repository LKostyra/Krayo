#pragma once

#include "Krayo/ApiDef.hpp"

#include <string>


namespace Krayo {
namespace Scene {
namespace Internal {

enum class ComponentType: unsigned char
{
    Invalid = 0,
    Model,
    Light,
    Emitter,
};

class Component
{
protected:
    std::string mName;

public:
    KRAYO_API Component(const std::string& name);

    KRAYO_API virtual ComponentType GetType() const = 0;

    KRAYO_INLINE std::string GetName() const
    {
        return mName;
    }
};

} // namespace Internal
} // namespace Scene
} // namespace Krayo
