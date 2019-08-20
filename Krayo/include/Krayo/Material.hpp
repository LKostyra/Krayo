#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include <string>


namespace Krayo {

class Material final
{
    Resources::Material* mImpl;

public:
    Material(Resources::Material* matImpl);
    ~Material();

    KRAYO_API void SetColor(float R, float G, float B);
};

} // namespace Krayo
