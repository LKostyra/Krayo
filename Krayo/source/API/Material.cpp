#include "Krayo/Material.hpp"
#include "Resources/Material.hpp"


namespace Krayo {

Material::Material(Resources::Material* matImpl)
    : mImpl(matImpl)
{
}

Material::~Material()
{
}

void Material::SetColor(float R, float G, float B)
{
    mImpl->SetColor(R, G, B);
}

} // namespace Krayo
