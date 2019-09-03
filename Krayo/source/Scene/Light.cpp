#include "Scene/Light.hpp"


namespace Krayo {
namespace Scene {
namespace Internal {

Light::Light(const std::string& name)
    : Component(name)
{
}

Light::~Light()
{
}

} // namespace Internal
} // namespace Scene
} // namespace Krayo
