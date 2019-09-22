#include "Krayo/Map.hpp"

#include "Krayo/Object.hpp"
#include "Krayo/Component/Model.hpp"
#include "Krayo/Component/Transform.hpp"

#include "Map.hpp"
#include "Component/Model.hpp"
#include "Component/Transform.hpp"


namespace Krayo {

Map::Map(Internal::Map* impl)
    : mImpl(impl)
{
}

Map::~Map()
{
}

Component::Model* Map::CreateModelComponent(const std::string& name)
{
    return new Component::Model(dynamic_cast<Component::Internal::Model*>(
        mImpl->CreateComponent(Component::Type::Model, name)
    ));
}

Component::Transform* Map::CreateTransformComponent(const std::string& name)
{
    return new Component::Transform(dynamic_cast<Component::Internal::Transform*>(
        mImpl->CreateComponent(Component::Type::Transform, name)
    ));
}

Object* Map::CreateObject(const std::string& name)
{
    return new Object(mImpl->CreateObject(name));
}

} // namespace Krayo
