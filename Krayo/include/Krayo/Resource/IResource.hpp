#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include <string>
#include <memory>


namespace Krayo {
namespace Resource {

class IResource
{
protected:
    Internal::IResource* mImpl;

    IResource(Internal::IResource* impl);

public:
    KRAYO_API virtual bool Load(const std::string& path) = 0;
};

} // namespace Resource
} // namespace Krayo
