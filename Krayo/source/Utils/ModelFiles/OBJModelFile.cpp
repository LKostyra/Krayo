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

uint32_t OBJModelFile::GetMeshCount() const
{
    return 0;
}

void OBJModelFile::Close()
{
}

} // namespace Utils
} // namespace Krayo
