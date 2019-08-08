#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include <string>


namespace Krayo {

class Material final
{
    Scene::Material* mImpl;

public:
    Material(const std::string& name);
    ~Material();

    KRAYO_API void SetColor(float R, float G, float B);
};

} // namespace Krayo
