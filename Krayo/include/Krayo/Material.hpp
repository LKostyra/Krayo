#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include <string>


namespace Krayo {

class Material final
{
    Resource::Internal::Material* mImpl;

public:
    Material(Resource::Internal::Material* impl);
    ~Material();

    KRAYO_API void SetColor(float R, float G, float B);
};

} // namespace Krayo
