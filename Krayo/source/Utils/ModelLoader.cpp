#include "ModelLoader.hpp"


namespace Krayo {
namespace Utils {


ModelLoader::ModelType ModelLoader::DetermineModelType(const std::string& path)
{
    return ModelType::Unknown;
}

ModelFile* ModelLoader::OpenFBX(const std::string& path)
{
    return nullptr;
}

ModelFile* ModelLoader::OpenOBJ(const std::string& path)
{
    return nullptr;
}

ModelFile* ModelLoader::Open(const std::string& path)
{
    return nullptr;
}


} // namespace Utils
} // namespace Krayo
