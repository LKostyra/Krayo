#include "Krayo/Map.hpp"

#include "Krayo/Object.hpp"
#include "Krayo/Component/Model.hpp"
#include "Krayo/Component/Transform.hpp"

#include "Object.hpp"
#include "Map.hpp"
#include "Component/Model.hpp"
#include "Component/Transform.hpp"


namespace Krayo {

Map::Map(const std::shared_ptr<Internal::Map>& impl)
    : mImpl(impl)
{
}

Map::~Map()
{
}

Component::Model Map::CreateModelComponent(const std::string& name)
{
    return Component::Model(std::dynamic_pointer_cast<Component::Internal::Model>(
        mImpl->CreateComponent(Component::Type::Model, name)
    ));
}

Component::Transform Map::CreateTransformComponent(const std::string& name)
{
    return Component::Transform(std::dynamic_pointer_cast<Component::Internal::Transform>(
        mImpl->CreateComponent(Component::Type::Transform, name)
    ));
}

Object Map::CreateObject(const std::string& name)
{
    return Object(mImpl->CreateObject(name));
}

} // namespace Krayo
