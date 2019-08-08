#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include "Krayo/Object.hpp"
#include "Krayo/Component.hpp"
#include "Krayo/Material.hpp"


namespace Krayo {

class Map final
{
    friend class Krayo::Engine;

    Scene::Map* mImpl;


public:
    Map(const std::string& name);
    ~Map();

    /**
     * Create a new Object on the scene.
     *
     * @return Pointer for an object, nullptr on error.
     */
    KRAYO_API Krayo::Object* CreateObject(const std::string& name);

    /**
     * Create a new Component.
     *
     * @p[in] type Type of component to create.
     * @p[in] name Name of created component.
     * @return Pointer for an object, nullptr on error.
     */
    KRAYO_API Krayo::Component* CreateComponent(const Krayo::ComponentType type, const std::string& name);
};

} // namespace Krayo
