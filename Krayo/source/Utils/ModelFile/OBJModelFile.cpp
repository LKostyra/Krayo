#include "OBJModelFile.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <fstream>


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
    if (path.rfind(".obj") == std::string::npos)
    {
        LOGI("Provided file does not have .obj extension");
        return false;
    }

    std::ifstream file(path);
    if (!file)
    {
        LOGI("OBJ file cannot be opened");
        return false;
    }

    LOGI("Provided file " << path << " is a readable OBJ file");
    return true;
}

bool OBJModelFile::Open(const std::string& path)
{
    tinyobj::ObjReaderConfig readerConfig;
    readerConfig.triangulate = true;
    readerConfig.vertex_color = false;

    tinyobj::ObjReader reader;
    bool loaded = reader.ParseFromFile(path, readerConfig);

    if (!reader.Warning().empty())
    {
        LOGW("Warnings while parsing OBJ file " << path << ":");
        LOGW(reader.Warning());
    }

    if (!loaded)
    {
        LOGE("Failed to parse OBJ file " << path << ":");
        LOGE(reader.Error());
        return false;
    }

    LOGD("Loading OBJ file " << path << ":");
    LOGD("    Vertex count:   " << reader.GetAttrib().vertices.size());
    LOGD("    Normal count:   " << reader.GetAttrib().normals.size());
    LOGD("    Texcoord count: " << reader.GetAttrib().texcoords.size());
    LOGD("    Material count: " << reader.GetMaterials().size());
    LOGD("    Shape count:    " << reader.GetShapes().size());

    for (uint32_t i = 0; i < reader.GetShapes().size(); ++i)
    {
        LOGD("    Shape " << i << ":");
        LOGD("      Name :             " << reader.GetShapes()[i].name);
        LOGD("      Material id count: " << reader.GetShapes()[i].mesh.material_ids.size());
        LOGD("      Index count:       " << reader.GetShapes()[i].mesh.indices.size());
    }

    return false;
}

void OBJModelFile::Close()
{
}

} // namespace Utils
} // namespace Krayo
