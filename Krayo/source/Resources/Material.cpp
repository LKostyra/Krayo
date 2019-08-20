#include "Material.hpp"


namespace Krayo {
namespace Resources {

Material::Material(const std::string& name)
    : Resource(name)
{
}

bool Material::Load(const std::string& path)
{
    // not yet implemented
    // TODO make a material loading from JSON, or from own format?
    return false;
}

} // namespace Resources
} // namespace Krayo
