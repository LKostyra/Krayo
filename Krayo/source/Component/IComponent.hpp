#pragma once

#include "Krayo/Component/Type.hpp"
#include "Krayo/Component/IComponent.hpp"

#include "Utils/TypeID.hpp"

#include <string>


namespace Krayo {
namespace Component {
namespace Internal {

class IComponent
{
    std::string mName;

public:
    IComponent(const std::string& name);
    virtual ~IComponent();

    virtual const uint32_t GetTypeID() const = 0;
};

template <typename T>
class ComponentBase: public IComponent
{
    static const uint32_t mComponentTypeID;

public:
    ComponentBase(const std::string& name)
        : IComponent(name)
    {
    }

    virtual const uint32_t GetTypeID() const override { return mComponentTypeID; }
    static const uint32_t GetTypeIDStatic() { return mComponentTypeID; }
};

template <typename T>
const uint32_t ComponentBase<T>::mComponentTypeID = Utils::TypeID<IComponent>::Get<T>();

} // namespace Internal
} // namespace Component
} // namespace Krayo
