#pragma once

#include "ModelFile/IModelFile.hpp"

#include <string>
#include <memory>


namespace Krayo {
namespace Utils {

class ModelLoader
{
    static ModelFileType DetermineModelType(const std::string& path);

public:
    static std::unique_ptr<IModelFile> Open(const std::string& path);
};

} // namespace Utils
} // namespace Krayo
