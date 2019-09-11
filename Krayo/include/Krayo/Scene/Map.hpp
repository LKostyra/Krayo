#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include "Krayo/Scene/Object.hpp"

#include <memory>


namespace Krayo {
namespace Scene {

class Map final
{
    friend class Krayo::Engine;

    std::shared_ptr<Scene::Internal::Map> mImpl;

    Map(const std::shared_ptr<Scene::Internal::Map>& mapImpl);

public:
    /**
     * Create a new Object on the scene.
     *
     * @return Pointer for an object, nullptr on error.
     */
    KRAYO_API Krayo::Scene::Object CreateObject(const std::string& name);

    /**
     * Create a new Component.
     *
     * @p[in] type Type of component to create.
     * @p[in] name Name of created component.
     * @return Pointer for an object, nullptr on error.
     */
    //KRAYO_API Krayo::Scene::Component CreateComponent(const Krayo::Scene::ComponentType type, const std::string& name);
};

} // namespace Scene
} // namespace Krayo
