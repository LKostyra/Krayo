#include "Map.hpp"

#include <lkCommon/Utils/Logger.hpp>

#include "Component/Model.hpp"
#include "Component/Transform.hpp"
#include "Utils/TypeID.hpp"


namespace Krayo {
namespace Internal {

Map::Map(const std::string& name)
    : mName(name)
    , mComponentContainers(Utils::TypeID<Component::Internal::IComponent>::Count())
{
    LOGD("Component containers: " << mComponentContainers.size());
}

template <typename T>
Component::Internal::IComponent* Map::CreateComponentGeneric(ComponentContainer& c, const std::string& name)
{
    c.emplace_back(std::make_shared<T>(name));
    LOGD("Created Component " << reinterpret_cast<void*>(c.back().get()));
    return c.back().get();
}

Component::Internal::IComponent* Map::CreateComponent(Component::Type type, const std::string& name)
{
    LKCOMMON_ASSERT(static_cast<uint32_t>(type) < static_cast<uint32_t>(Component::Type::Count),
                    "Component Type invalid (out of range)");
    ComponentContainer& c = mComponentContainers[static_cast<uint32_t>(type)];

    switch (type)
    {
    case Component::Type::Model:
        return CreateComponentGeneric<Component::Internal::Model>(c, name);
    case Component::Type::Transform:
        return CreateComponentGeneric<Component::Internal::Transform>(c, name);
    default:
        LOGE("Unknown Component type: " << static_cast<uint32_t>(type));
        return nullptr;
    };
}

Internal::Object* Map::CreateObject(const std::string& name)
{
    mObjectContainer.emplace_back(std::make_shared<Object>(name));
    return mObjectContainer.back().get();
}

} // namespace Internal
} // namespace Krayo
