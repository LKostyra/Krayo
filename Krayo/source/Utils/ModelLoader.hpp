#pragma once

#include "IModelFile.hpp"

#include <string>


namespace Krayo {
namespace Utils {

class ModelLoader
{
    IModelFile* OpenFBX(const std::string& path);
    IModelFile* OpenOBJ(const std::string& path);

public:
    IModelFile* Open(const std::string& path);
};

} // namespace Utils
} // namespace Krayo
