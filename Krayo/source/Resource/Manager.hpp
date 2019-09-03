#pragma once

#include "IResource.hpp"

#include "Krayo/Resource/Type.hpp"

#include <map>
#include <memory>


namespace Krayo {
namespace Resource {
namespace Internal {

class Manager
{
    using ResourcePtr = std::shared_ptr<IResource>;
    using ResourceContainer = std::map<std::string, ResourcePtr>;

    ResourceContainer mResources;

public:
    std::shared_ptr<IResource> CreateResource(const Krayo::Resource::Type type, const std::string& name);
    std::shared_ptr<IResource> GetResource(const std::string& name);
};

} // namespace Internal
} // namespace Resource
} // namespace Krayo
