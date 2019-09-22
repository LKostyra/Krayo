#include "Manager.hpp"

#include "Resource/Model.hpp"
#include "Utils/TypeID.hpp"

#include <lkCommon/lkCommon.hpp>
#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Resource {
namespace Internal {


Manager::Manager()
    : mResourceContainers(Utils::TypeID<IResource>::Count())
{
    LOGD("Resource Container: " << mResourceContainers.size());
}

template <typename T>
IResource* Manager::CreateResourceGeneric(ResourceContainer& c, const std::string& name)
{
    c.emplace_back(std::make_shared<T>(name));
    LOGD("Created Resource " << reinterpret_cast<void*>(c.back().get()));
    return c.back().get();
}

IResource* Manager::CreateResource(const Krayo::Resource::Type type, const std::string& name)
{
    LKCOMMON_ASSERT(static_cast<uint32_t>(type) < static_cast<uint32_t>(Resource::Type::Count),
                    "Resource Type invalid (out of range)");
    ResourceContainer& c = mResourceContainers[static_cast<size_t>(type)];

    switch (type)
    {
    case Type::Model:
        return CreateResourceGeneric<Model>(c, name);
    default:
        LOGE("Unknown resource type to create");
        return nullptr;
    }
}


} // namespace Internal
} // namespace Resource
} // namespace Krayo
