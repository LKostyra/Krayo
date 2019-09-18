#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include <string>


namespace Krayo {
namespace Resource {

class Manager final
{
    friend class Krayo::Engine;

    Internal::Manager& mImpl;

    Manager(Internal::Manager& manager);
    ~Manager() = default;

public:

};

} // namespace Resource
} // namespace Krayo
