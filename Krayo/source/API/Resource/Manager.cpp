#include "Krayo/Resource/Manager.hpp"
#include "Resource/Manager.hpp"

#include "Krayo/Resource/Model.hpp"

#include "Resource/Model.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Resource {

Manager::Manager(Internal::Manager& manager)
    : mImpl(manager)
{
}

Model* Manager::CreateModel(const std::string& name)
{
    return new Model(dynamic_cast<Internal::Model*>(mImpl.CreateResource(Type::Model, name)));
}

} // namespace Resource
} // namespace Krayo
