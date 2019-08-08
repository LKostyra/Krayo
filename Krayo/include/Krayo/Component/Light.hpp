#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"


namespace Krayo {

class Light final
{
    friend class Engine;

    Scene::Light* mImpl;

    Light(Scene::Light* impl);
    ~Light();

public:
    KRAYO_API void SetPosition(const float x, const float y, const float z);
    KRAYO_API void SetDiffuseIntensity(const float R, const float G, const float B);
    KRAYO_API void SetRange(const float range);
};

} // namespace Krayo
