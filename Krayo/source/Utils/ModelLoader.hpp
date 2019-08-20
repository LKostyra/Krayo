#pragma once

#include "ModelFile.hpp"

#include <string>


namespace Krayo {
namespace Utils {

class ModelLoader
{
    ModelFile* OpenFBX(const std::string& path);
    ModelFile* OpenOBJ(const std::string& path);

public:
    ModelFile* Open(const std::string& path);
};

} // namespace Utils
} // namespace Krayo
