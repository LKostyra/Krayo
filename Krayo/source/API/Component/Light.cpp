#include "Krayo/Component/Light.hpp"

#include "Scene/Light.hpp"


namespace Krayo {

Light::Light(Scene::Light* light)
    : mImpl(light)
{
}

Light::~Light()
{
}

void Light::SetPosition(const float x, const float y, const float z)
{
    mImpl->SetPosition(x, y, z);
}

void Light::SetDiffuseIntensity(const float R, const float G, const float B)
{
    mImpl->SetDiffuseIntensity(R, G, B);
}

void Light::SetRange(const float range)
{
    mImpl->SetRange(range);
}

} // namespace Krayo
