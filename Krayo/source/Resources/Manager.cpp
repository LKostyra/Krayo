#include "Manager.hpp"

#include "Model.hpp"
#include "Material.hpp"
#include "Texture.hpp"


namespace Krayo {
namespace Resources {

Resource* Manager::CreateResource(const ResourceType type, const std::string& name)
{
    switch (type)
    {
    case ResourceType::Model:
        mResources.push_back(std::make_unique<Krayo::Resources::Model>(name));
        break;
    case ResourceType::Material:
        mResources.push_back(std::make_unique<Krayo::Resources::Material>(name));
        break;
    case ResourceType::Texture:
        mResources.push_back(std::make_unique<Krayo::Resources::Texture>(name));
        break;
    }
}

} // namespace Krayo
} // namespace Resources
