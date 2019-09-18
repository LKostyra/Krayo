#include "Manager.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Resource {
namespace Internal {


std::shared_ptr<IResource> Manager::CreateResource(const Krayo::Resource::Type type, const std::string& name)
{
    std::pair<ResourceContainer::iterator, bool> result;

    switch (type)
    {
    default:
        LOGE("Unknown resource type");
        return nullptr;
    }

    if (!result.second)
    {
        LOGE("Resource of name " << name << " already exists!");
        return nullptr;
    }

    return result.first->second;
}

std::shared_ptr<IResource> Manager::GetResource(const std::string& name)
{
    auto res = mResources.find(name);
    if (res == mResources.end())
    {
        LOGE("Resource " << name << " does not exist.");
        return nullptr;
    }

    return res->second;
}

} // namespace Internal
} // namespace Resources
} // namespace Krayo
