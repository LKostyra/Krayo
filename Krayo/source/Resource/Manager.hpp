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
    std::shared_ptr<Internal::IResource> CreateResourceGeneric(ResourceContainer& c, const std::string& name);

    std::string GetModelNameFromPath(const std::string& path);

public:
    Manager();

    std::shared_ptr<Internal::IResource> CreateResource(const Krayo::Resource::Type type, const std::string& name);

    bool LoadFile(const std::string& path);
    std::shared_ptr<Internal::IResource> GetResource(const Krayo::Resource::Type type, const std::string& name);
};

} // namespace Internal
} // namespace Resource
} // namespace Krayo
