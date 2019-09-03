#include "Krayo/Resource/Manager.hpp"

#include "Resource/Manager.hpp"
#include "Resource/Model.hpp"


namespace Krayo {
namespace Resource {

Manager::Manager(Internal::Manager& manager)
    : mImpl(manager)
{
}

Model Manager::CreateModel(const std::string& name)
{
    return Model(std::dynamic_pointer_cast<Internal::Model>(mImpl.CreateResource(Type::Model, name)));
}

Model Manager::GetModel(const std::string& name)
{
    return Model(std::dynamic_pointer_cast<Internal::Model>(mImpl.GetResource(name)));
}

} // namespace Resource
} // namespace Krayo
