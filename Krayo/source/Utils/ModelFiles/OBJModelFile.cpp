#include "OBJModelFile.hpp"


namespace Krayo {
namespace Utils {

OBJModelFile::OBJModelFile()
{
}

OBJModelFile::~OBJModelFile()
{
}

bool OBJModelFile::ProbeFile(const std::string& path)
{
    LOGE("OBJ files not yet supported");
    return false;
}

bool OBJModelFile::Open(const std::string& path)
{
    return false;
}

void OBJModelFile::Close()
{
}

} // namespace Utils
} // namespace Krayo
