#include "Map.hpp"

#include <lkCommon/Utils/Logger.hpp>

#include "Component/Model.hpp"
#include "Component/Transform.hpp"
#include "Component/Camera.hpp"
#include "Utils/TypeID.hpp"


namespace Krayo {
namespace Internal {

Map::Map(const std::string& name)
    : mName(name)
    , mNullComponent(nullptr)
    , mComponentContainers(Utils::TypeID<Component::Internal::IComponent>::Count())
{
    LOGD("Component containers: " << mComponentContainers.size());
}

template <typename T>
std::shared_ptr<Component::Internal::IComponent>& Map::CreateComponentGeneric(ComponentContainer& c, const std::string& name)
{
    c.emplace_back(new T(name));
    LOGD("Created Component " << reinterpret_cast<void*>(c.back().get()));
    return c.back();
}

std::shared_ptr<Component::Internal::IComponent>& Map::CreateComponent(Component::Type type, const std::string& name)
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
    case Component::Type::Camera:
        return CreateComponentGeneric<Component::Internal::Camera>(c, name);
    default:
        LOGE("Unknown Component type: " << static_cast<uint32_t>(type));
        return mNullComponent;
    };
}

std::shared_ptr<Internal::Object>& Map::CreateObject(const std::string& name)
{
    mObjectContainer.emplace_back(std::make_shared<Object>(name));
    return mObjectContainer.back();
}

void Map::ForEachObject(const Callback<Object>& callback) const
{
    for (const auto& o: mObjectContainer)
        if (!callback(o.get()))
            break;
}

} // namespace Internal
} // namespace Krayo
