#pragma once

#include <string>
#include <vector>

#include "Component/IComponent.hpp"


namespace Krayo {
namespace Internal {

class Object final
{
    std::string mName;

    std::vector<std::shared_ptr<Component::Internal::IComponent>> mComponents;

public:
    Object(const std::string& name);
    ~Object() = default;

    void AttachComponent(std::shared_ptr<Component::Internal::IComponent>& component);

    template <typename T>
    const T* GetComponent() const
    {
        return dynamic_cast<T*>(mComponents[T::GetTypeIDStatic()].get());
    }
};

} // namespace Internal
} // namespace Krayo
