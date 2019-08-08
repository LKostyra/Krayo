#pragma once

#include "Prerequisites.hpp"
#include "Krayo/Object.hpp"
#include "Scene/Model.hpp"
#include "Scene/Light.hpp"
#include "Scene/Emitter.hpp"

#include <lkCommon/Utils/Pixel.hpp>

#include <unordered_map>


namespace Krayo {
namespace Scene {

template <typename T>
using Callback = std::function<bool(const T*)>; // return false to stop iterating

template <typename T>
using CreateResult = T*;

class Map
{
    template <typename T>
    using ResourceCollection = std::vector<T>;

    std::string mName;
    ResourceCollection<Krayo::Object> mObjects;
    ResourceCollection<Model> mModelComponents;
    ResourceCollection<Light> mLightComponents;
    ResourceCollection<Emitter> mEmitterComponents;

    // template helpers
    template <typename ItemType>
    CreateResult<ItemType> CreateItem(ResourceCollection<ItemType>& m, const std::string& name);
    template <typename ItemType>
    void ForEachItem(const ResourceCollection<ItemType>& m, Callback<ItemType>& func) const;

public:
    Map(const std::string& name);
    ~Map();

    CreateResult<Krayo::Object> CreateObject(const std::string& name);
    CreateResult<Krayo::Component> CreateComponent(Krayo::ComponentType type, const std::string& name);
    void ForEachLight(Callback<Light> func) const;
    void ForEachEmitter(Callback<Emitter> func) const;
    void ForEachObject(Callback<Krayo::Object> func) const;

    LKCOMMON_INLINE uint32_t GetEmitterCount() const
    {
        return static_cast<uint32_t>(mEmitterComponents.size());
    }
};

} // namespace Scene
} // namespace Krayo
