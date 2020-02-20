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

bool Manager::LoadFile(const std::string& path)
{
    return mImpl.LoadFile(path);
}

Model Manager::GetModel(const std::string& name)
{
    Internal::Model* m = dynamic_cast<Internal::Model*>(
        mImpl.GetResource(Type::Model, name)
    );
    if (!m)
        return Model(nullptr);

    return Model(m);
}

} // namespace Resource
} // namespace Krayo
