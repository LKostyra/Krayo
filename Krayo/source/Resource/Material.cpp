#include "Material.hpp"


namespace Krayo {
namespace Resource {
namespace Internal {

Material::Material(const std::string& name)
    : IResource(name)
{
}

bool Material::Load(const std::string& path)
{
    // not yet implemented
    // TODO make a material loading from JSON, or from own format?
    return false;
}

} // namespace Internal
} // namespace Resource
} // namespace Krayo
