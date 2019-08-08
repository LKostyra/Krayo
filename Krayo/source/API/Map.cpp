#include "Krayo/Map.hpp"
#include "Scene/Map.hpp"


namespace Krayo {

Map::Map(const std::string& name)
    : mImpl(new Scene::Map(name))
{
}

Map::~Map()
{
    delete mImpl;
    mImpl = nullptr;
}

Krayo::Object* Map::CreateObject(const std::string& name)
{
    Scene::CreateResult<Krayo::Object> object = mImpl->CreateObject(name);
    return object;
}

Krayo::Component* Map::CreateComponent(const Krayo::ComponentType type, const std::string& name)
{
    Scene::CreateResult<Krayo::Component> component = mImpl->CreateComponent(type, name);
    return component;
}

} // namespace Krayo
