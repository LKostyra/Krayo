#pragma once

#include "ModelFile.hpp"

#include <string>


namespace Krayo {
namespace Utils {

class ModelLoader
{
    enum class ModelType
    {
        Unknown = 0,
        FBX,
        OBJ,
    };

    static ModelType DetermineModelType(const std::string& path);

    static ModelFile* OpenFBX(const std::string& path);
    static ModelFile* OpenOBJ(const std::string& path);

public:
    static ModelFile* Open(const std::string& path);
};

} // namespace Utils
} // namespace Krayo
