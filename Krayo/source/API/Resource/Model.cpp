#include "Krayo/Resource/Model.hpp"

#include "Resource/Model.hpp"


namespace Krayo {
namespace Resource {

Model::Model(Internal::Model* model)
    : IResource(model)
{
}

bool Model::Load(const std::string& path)
{
    return mImpl->Load(path);
}

bool Model::LoadMesh(const std::vector<float>& vertices)
{
    return dynamic_cast<Internal::Model*>(mImpl)->LoadMesh(vertices);
}

} // namespace Resource
} // namespace Krayo
