#include "Model.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Resource {
namespace Internal {

Model::Model(const std::string& name)
    : ResourceBase<Model>(name)
{
}

bool Model::Load(const std::string& path)
{
    Utils::ModelFile* file = Utils::ModelLoader::Open(path);

    if (file == nullptr)
    {
        LOGE("Failed to load Model from file");
        return false;
    }

    return true;
}

} // namespace Internal
} // namespace Resource
} // namespace Krayo
