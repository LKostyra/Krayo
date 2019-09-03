#include "Krayo/Scene/Map.hpp"
#include "Scene/Map.hpp"


namespace Krayo {
namespace Scene {

Map::Map(const std::shared_ptr<Internal::Map>& impl)
    : mImpl(impl)
{
}

Krayo::Scene::Object Map::CreateObject(const std::string& name)
{
    return Krayo::Scene::Object(mImpl->CreateObject(name));
}
/*
Krayo::Component Map::CreateComponent(const Krayo::ComponentType type, const std::string& name)
{
    return Krayo::Component(mImpl->CreateComponent(type, name));
}*/

} // namespace Scene
} // namespace Krayo
