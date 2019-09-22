#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"
#include "Krayo/Component/Type.hpp"
#include "Krayo/Component/Model.hpp"

#include <string>


namespace Krayo {

class Map final
{
    friend class Engine;

    Internal::Map* mImpl;

    Map(Internal::Map* impl);

    Component::Internal::IComponent* CreateComponent(Component::Type type, const std::string& name);

public:
    /**
     * Destroys Map object
     */
    KRAYO_API ~Map();

    /**
     * Create a Model Component in current map
     */
    KRAYO_API Component::Model* CreateModelComponent(const std::string& name);

    /**
     * Create a Transform Component in current map
     */
    KRAYO_API Component::Transform* CreateTransformComponent(const std::string& name);

    /**
     * Create an Object in map
     */
    KRAYO_API Object* CreateObject(const std::string& name);
};

} // namespace Krayo
