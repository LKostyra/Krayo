#pragma once

#include "Resource/IResource.hpp"

#include "Krayo/Resource/Type.hpp"

#include <vector>
#include <memory>


namespace Krayo {
namespace Resource {
namespace Internal {

class Manager
{
    using ResourcePtr = std::shared_ptr<IResource>;
    using ResourceContainer = std::vector<ResourcePtr>;

    std::vector<ResourceContainer> mResourceContainers;

    template <typename T>
    Internal::IResource* CreateResourceGeneric(ResourceContainer& c, const std::string& name);

public:
    Manager();

    Internal::IResource* CreateResource(const Krayo::Resource::Type type, const std::string& name);
};

} // namespace Internal
} // namespace Resource
} // namespace Krayo
