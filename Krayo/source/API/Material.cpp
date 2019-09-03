#include "Krayo/Material.hpp"

#include "Resource/Material.hpp"


namespace Krayo {

Material::Material(Resource::Internal::Material* matImpl)
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
