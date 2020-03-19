#pragma once

#include <string>
#include <array>

#include <lkCommon/Utils/Logger.hpp>

#include "Component/IComponent.hpp"
#include "Krayo/Component/Type.hpp"


namespace Krayo {
namespace Internal {

class Object final
{
    std::string mName;
    std::array<Component::ComponentID, static_cast<size_t>(Component::Type::Count)> mComponents;

public:
    Object::Object(const std::string& name)
        : mName(name)
        , mComponents()
    {
    }

    ~Object() = default;

    template <typename T>
    void AttachComponent(Component::ComponentID componentID)
    {
        mComponents[T::GetTypeIDStatic()] = componentID;
        LOGD("Attached component " << componentID << " as type " << T::GetTypeIDStatic());
    }

    template <typename T>
    const T* GetComponent() const
    {
        const Component::ComponentID id = mComponents[T::GetTypeIDStatic()];
        return dynamic_cast<T*>();
    }
};

} // namespace Internal
} // namespace Krayo
