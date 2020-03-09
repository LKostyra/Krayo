#pragma once

#include "Krayo/Component/Type.hpp"

#include "Component/IComponent.hpp"
#include "Object.hpp"

#include <string>
#include <memory>
#include <vector>
#include <functional>


namespace Krayo {
namespace Internal {

class Map
{
    template <typename T>
    using Callback = std::function<bool(const T*)>;

    template <typename T>
    using Container = std::vector<std::shared_ptr<T>>;

    using ComponentContainer = Container<Component::Internal::IComponent>;

    std::string mName;
    std::shared_ptr<Component::Internal::IComponent> mNullComponent;
    std::vector<ComponentContainer> mComponentContainers;
    Container<Object> mObjectContainer;

    template <typename T>
    std::shared_ptr<Component::Internal::IComponent>& CreateComponentGeneric(ComponentContainer& c, const std::string& name);


public:
    Map(const std::string& name);
    ~Map() = default;

    std::shared_ptr<Component::Internal::IComponent>& CreateComponent(Component::Type type, const std::string& name);
    std::shared_ptr<Internal::Object>& CreateObject(const std::string& name);

    void ForEachObject(const Callback<Object>& callback) const;

    template <typename T>
    void ForEachComponent(const Callback<T>& callback) const
    {
        ComponentContainer& c = mComponentContainers[T::GetTypeIDStatic()];
        for (const auto& o: c)
            if (!callback(o.get()))
                break;
    }
};

} // namespace Internal
} // namespace Krayo
