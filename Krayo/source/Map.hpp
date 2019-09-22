#pragma once

#include "Krayo/Component/Type.hpp"

#include "Component/IComponent.hpp"
#include "Object.hpp"

#include <string>
#include <memory>
#include <vector>


namespace Krayo {
namespace Internal {

class Map
{
    template <typename T>
    using Ptr = std::shared_ptr<T>;
    template <typename T>
    using Container = std::vector<Ptr<T>>;

    using ComponentContainer = Container<Component::Internal::IComponent>;

    std::string mName;
    std::vector<ComponentContainer> mComponentContainers;
    Container<Object> mObjectContainer;

    template <typename T>
    Component::Internal::IComponent* CreateComponentGeneric(ComponentContainer& c, const std::string& name);


public:
    Map(const std::string& name);
    ~Map() = default;

    Component::Internal::IComponent* CreateComponent(Component::Type type, const std::string& name);
    Internal::Object* CreateObject(const std::string& name);
};

} // namespace Krayo
} // namespace Internal
