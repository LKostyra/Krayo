#include "ModelLoader.hpp"

#include "ModelFiles/FBXModelFile.hpp"
#include "ModelFiles/OBJModelFile.hpp"

#include <array>
#include <functional>


namespace Krayo {
namespace Utils {

using FileProber = std::function<bool(const std::string& path)>;

struct ModelFormat
{
    ModelFileType type;
    FileProber probe;

    ModelFormat(ModelFileType type, const FileProber& prober)
        : type(type), probe(prober)
    {
    }
};

const std::array<ModelFormat, 2> SupportedFormats {
    ModelFormat(ModelFileType::FBX, FBXModelFile::ProbeFile),
    ModelFormat(ModelFileType::OBJ, OBJModelFile::ProbeFile),
};

ModelFileType ModelLoader::DetermineModelType(const std::string& path)
{
    for (auto& format: SupportedFormats)
        if (format.probe(path))
            return format.type;

    return ModelFileType::Unknown;
}

std::unique_ptr<IModelFile> ModelLoader::Open(const std::string& path)
{
    ModelFileType type = DetermineModelType(path);

    std::unique_ptr<IModelFile> result;
    switch (type)
    {
    case ModelFileType::FBX:
        result = std::make_unique<FBXModelFile>();
        break;
    case ModelFileType::OBJ:
        result = std::make_unique<OBJModelFile>();
        break;
    default:
        LOGE("Unsupported model file " << path);
        return nullptr;
    }

    if (!result->Open(path))
    {
        LOGE("Failed to open Model file " << path);
        return nullptr;
    }

    return result;
}


} // namespace Utils
} // namespace Krayo
