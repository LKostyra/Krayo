#pragma once

#include "Prerequisites.hpp"
#include "Scene/Object.hpp"
#include "Component/IComponent.hpp"
#include "Component/Model.hpp"
#include "Component/Light.hpp"
#include "Component/Emitter.hpp"

#include <lkCommon/Utils/Pixel.hpp>

#include <map>


namespace Krayo {
namespace Scene {
namespace Internal {

template <typename T>
using Callback = std::function<bool(const T*)>; // return false to stop iterating

template <typename T>
using CreateResult = std::shared_ptr<T>;

class Map
{
    template <typename T>
    using ResourceCollection = std::map<std::string, std::shared_ptr<T>>;

    std::string mName;
    ResourceCollection<Object> mObjects;
    ResourceCollection<Component::Internal::Model> mModelComponents;
    ResourceCollection<Component::Internal::Light> mLightComponents;
    ResourceCollection<Component::Internal::Emitter> mEmitterComponents;

    // template helpers
    template <typename ItemType>
    CreateResult<ItemType> CreateItem(ResourceCollection<ItemType>& m, const std::string& name);
    template <typename ItemType>
    void ForEachItem(const ResourceCollection<ItemType>& m, Callback<ItemType>& func) const;

public:
    Map(const std::string& name);
    ~Map();

    CreateResult<Object> CreateObject(const std::string& name);
    CreateResult<Component::Internal::IComponent> CreateComponent(Component::Internal::Type type, const std::string& name);
    void ForEachLight(Callback<Component::Internal::Light> func) const;
    void ForEachEmitter(Callback<Component::Internal::Emitter> func) const;
    void ForEachObject(Callback<Object> func) const;

    LKCOMMON_INLINE uint32_t GetEmitterCount() const
    {
        return static_cast<uint32_t>(mEmitterComponents.size());
    }
};

} // namespace Internal
} // namespace Scene
} // namespace Krayo
