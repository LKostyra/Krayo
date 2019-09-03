#include "Manager.hpp"

#include "Model.hpp"
#include "Material.hpp"
#include "Texture.hpp"


namespace Krayo {
namespace Resource {
namespace Internal {


std::shared_ptr<IResource> Manager::CreateResource(const Krayo::Resource::Type type, const std::string& name)
{
    std::pair<ResourceContainer::iterator, bool> result;

    switch (type)
    {
    case Krayo::Resource::Type::Model:
        result = mResources.emplace(
            std::make_pair(name, std::make_shared<Krayo::Resource::Internal::Model>(name))
        );
        break;
    case Krayo::Resource::Type::Material:
        result = mResources.emplace(
            std::make_pair(name, std::make_shared<Krayo::Resource::Internal::Material>(name))
        );
        break;
    case Krayo::Resource::Type::Texture:
        result = mResources.emplace(
            std::make_pair(name, std::make_shared<Krayo::Resource::Internal::Texture>(name))
        );
        break;
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
