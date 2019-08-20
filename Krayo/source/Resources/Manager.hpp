#pragma once

#include "Resource.hpp"

#include <list>
#include <memory>


namespace Krayo {
namespace Resources {

class Manager
{
    std::list<std::unique_ptr<Resource>> mResources;

public:
    Resource* CreateResource(const ResourceType type, const std::string& name);
};

} // namespace Krayo
} // namespace Resources
