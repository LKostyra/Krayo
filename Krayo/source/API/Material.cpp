#include "Krayo/Material.hpp"
#include "Scene/Material.hpp"


namespace Krayo {

Material::Material(const std::string& name)
    : mImpl(new Scene::Material(name))
{
}

Material::~Material()
{
    delete mImpl;
    mImpl = nullptr;
}

void Material::SetColor(float R, float G, float B)
{
    mImpl->SetColor(R, G, B);
}

} // namespace Krayo
