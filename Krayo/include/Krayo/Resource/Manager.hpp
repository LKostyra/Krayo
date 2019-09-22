#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include "Krayo/Resource/IResource.hpp"
#include "Krayo/Resource/Type.hpp"

#include <string>


namespace Krayo {
namespace Resource {

class Manager final
{
    friend class Krayo::Internal::Engine;

    Internal::Manager& mImpl;

    Manager(Internal::Manager& manager);
    ~Manager() = default;

public:
    KRAYO_API Model* CreateModel(const std::string& name);
};

} // namespace Resource
} // namespace Krayo
