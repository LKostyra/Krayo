#include "KrayoJSONModelFile.hpp"

#include <lkCommon/Math/Vector3.hpp>
#include <rapidjson/document.h>
#include <fstream>


namespace {

const std::string MODEL_NAME_NODE_NAME = "name";
const std::string MODEL_MESHES_NODE_NAME = "meshes";
const std::string MODEL_MESH_MATERIAL_NODE_NAME = "material";
const std::string MODEL_MESH_VERTICES_NODE_NAME = "vertices";
const std::string MODEL_MESH_NORMALS_NODE_NAME = "normals";
const std::string MODEL_MESH_TANGENTS_NODE_NAME = "tangents";
const std::string MODEL_MESH_UVS_NODE_NAME = "uvs";
const std::string MODEL_MESH_INDICES_NODE_NAME = "indices";

} // namespace


namespace Krayo {
namespace Utils {

KrayoJSONModelFile::KrayoJSONModelFile()
{
}

KrayoJSONModelFile::~KrayoJSONModelFile()
{
}

bool KrayoJSONModelFile::InitializeMesh(const rapidjson::Value& node, FileMesh& mesh)
{
    // do all the preallocation before loading the data
    // at this point file was already validated, so just do the getting
    uint32_t vertCount = 0, indexCount = 0;
    for (auto& o: node.GetObject())
    {
        if (MODEL_MESH_VERTICES_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            vertCount = o.value.GetArray().Size();
        }

        if (MODEL_MESH_INDICES_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            indexCount = o.value.GetArray().Size();
        }
    }

    mesh.mVertexBuffer.resize(vertCount);
    mesh.mVertexBufferParams.resize(vertCount);
    mesh.mIndexBuffer.resize(indexCount);
    mesh.mPointCount = indexCount;
    LOGD("Mesh initialized with point count " << mesh.mPointCount);

    return true;
}

bool KrayoJSONModelFile::LoadVertices(const rapidjson::Value& node, FileMesh& mesh)
{
    const auto& vertices = node.GetArray();
    if (mesh.mVertexBuffer.size() != vertices.Size())
    {
        LOGE("Space for vertices is not allocated properly");
        return false;
    }

    for (uint32_t i = 0; i < vertices.Size(); ++i)
    {
        const auto& vert = vertices[i].GetArray();
        mesh.mVertexBuffer[i] = lkCommon::Math::Vector3(
            vert[0].GetFloat(),
            vert[1].GetFloat(),
            vert[2].GetFloat()
        );
    }

    return true;
}

bool KrayoJSONModelFile::LoadNormals(const rapidjson::Value& node, FileMesh& mesh)
{
    const auto& normals = node.GetArray();
    if (mesh.mVertexBufferParams.size() != normals.Size())
    {
        LOGE("Space for normals is not allocated properly");
        return false;
    }

    for (uint32_t i = 0; i < normals.Size(); ++i)
    {
        const auto& norm = normals[i].GetArray();
        mesh.mVertexBufferParams[i].normal = lkCommon::Math::Vector3(
            norm[0].GetFloat(),
            norm[1].GetFloat(),
            norm[2].GetFloat()
        );
    }

    return true;
}

bool KrayoJSONModelFile::LoadTangents(const rapidjson::Value& node, FileMesh& mesh)
{
    const auto& tangents = node.GetArray();
    if (mesh.mVertexBufferParams.size() != tangents.Size())
    {
        LOGE("Space for tangents is not allocated properly");
        return false;
    }

    for (uint32_t i = 0; i < tangents.Size(); ++i)
    {
        const auto& tang = tangents[i].GetArray();
        mesh.mVertexBufferParams[i].tangent = lkCommon::Math::Vector3(
            tang[0].GetFloat(),
            tang[1].GetFloat(),
            tang[2].GetFloat()
        );
    }

    return true;
}

bool KrayoJSONModelFile::LoadUVs(const rapidjson::Value& node, FileMesh& mesh)
{
    const auto& uvs = node.GetArray();
    if (mesh.mVertexBufferParams.size() != uvs.Size())
    {
        LOGE("Space for uvs is not allocated properly");
        return false;
    }

    for (uint32_t i = 0; i < uvs.Size(); ++i)
    {
        const auto& uv = uvs[i].GetArray();
        mesh.mVertexBufferParams[i].uv = lkCommon::Math::Vector2(
            uv[0].GetFloat(),
            uv[1].GetFloat()
        );
    }

    return true;
}

bool KrayoJSONModelFile::LoadIndices(const rapidjson::Value& node, FileMesh& mesh)
{
    const auto& indices = node.GetArray();
    for (uint32_t i = 0; i < indices.Size(); ++i)
    {
        mesh.mIndexBuffer[i] = indices[i].GetInt();
    }

    return true;
}

bool KrayoJSONModelFile::LoadMesh(const rapidjson::Value& node, FileMesh& mesh)
{
    if (!node.IsObject())
    {
        LOGE("Invalid object node");
        return false;
    }

    if (!InitializeMesh(node, mesh))
        return false;

    bool succeeded = true;
    for (auto& o: node.GetObject())
    {
        if (MODEL_MESH_MATERIAL_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            // TODO
            continue;
        }

        if (MODEL_MESH_VERTICES_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            if (!LoadVertices(o.value, mesh))
                return false;
        }

        if (MODEL_MESH_NORMALS_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            if (!LoadNormals(o.value, mesh))
                return false;
        }

        if (MODEL_MESH_TANGENTS_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            if (!LoadTangents(o.value, mesh))
                return false;
        }

        if (MODEL_MESH_UVS_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            if (!LoadUVs(o.value, mesh))
                return false;
        }

        if (MODEL_MESH_INDICES_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            if (!LoadIndices(o.value, mesh))
                return false;
        }
    }

    return true;
}

bool KrayoJSONModelFile::LoadMeshes(const rapidjson::Value& node)
{
    bool succeeded = true;
    LOGD("node member count " << node.GetObject().MemberCount());
    for (rapidjson::Value::ConstMemberIterator it = node.MemberBegin();
         it != node.MemberEnd();
         ++it)
    {
        if (MODEL_NAME_NODE_NAME.compare(it->name.GetString()) == 0)
        {
            mName.reserve(it->value.GetStringLength());
            mName = it->value.GetString();
            continue;
        }

        if (MODEL_MESHES_NODE_NAME.compare(it->name.GetString()) == 0)
        {
            mMeshes.resize(it->value.GetArray().Size());
            const auto& meshArray = it->value.GetArray();
            for (uint32_t i = 0; i < meshArray.Size(); ++i)
            {
                if (!LoadMesh(meshArray[i], mMeshes[i]))
                {
                    LOGE("Failed to load mesh " << i);
                    succeeded = false;
                }
            }
        }
    }

    return succeeded;
}

bool KrayoJSONModelFile::ValidateArrayOfCoords(const rapidjson::Value& node, const char* name,
                                               size_t dimensions, size_t& elements)
{
    if (!node.IsArray())
    {
        LOGE("   Field " << name << " should be an array");
        return false;
    }

    if (node.GetArray().Size() == 0)
    {
        LOGE("   Field " << name << " should be a non-empty array");
        return false;
    }

    LOGD("    \\_ " << node.GetArray().Size() << ' ' << name);
    const auto& elementsArray = node.GetArray();
    bool succeeded = true;
    for (const auto& e: elementsArray)
    {
        if (!e.IsArray())
        {
            LOGE("An element in " << name << " field should be an array");
            succeeded = false;
            break;
        }

        if (e.GetArray().Size() != dimensions)
        {
            LOGE("An element in " << name << " field must have " << dimensions << "-element float vertices");
            succeeded = false;
            break;
        }

        for (auto& f: e.GetArray())
        {
            if (!f.IsFloat())
            {
                LOGE("An element in " << name << " field must have " << dimensions << " -element float vertices");
                succeeded = false;
                break;
            }
        }
    }

    elements = elementsArray.Size();
    return succeeded;
}

bool KrayoJSONModelFile::ValidateIndices(const rapidjson::Value& node, uint32_t& maxInd)
{
    if (!node.IsArray())
    {
        LOGE("     indices field should be an array");
        return false;
    }

    if (node.GetArray().Size() == 0 || (node.GetArray().Size() % 3 != 0))
    {
        LOGE("     indices field should be a non-empty array " <<
             "and should have amount of elements divisable by three");
        return false;
    }

    LOGD("    \\_ " << node.GetArray().Size() << " indices");
    maxInd = 0;
    for (auto& ind: node.GetArray())
    {
        if (!ind.IsUint())
        {
            LOGE("     indices field should consist of only unsigned integers");
            return false;
        }

        if (ind.GetUint() > maxInd)
            maxInd = ind.GetUint();
    }

    return true;
}

bool KrayoJSONModelFile::ValidateMesh(const rapidjson::Value& node)
{
    if (!node.IsObject())
    {
        LOGE("   Provided node for mesh is not a JSON object");
        return false;
    }

    bool succeeded = true;
    size_t vertCount = 0, normalCount = 0, tangentCount = 0, uvCount = 0;
    uint32_t maxInd = 0;
    for (auto& o: node.GetObject())
    {
        LOGD("  \\_ " << o.name.GetString());

        if (MODEL_MESH_MATERIAL_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            if (!o.value.IsString())
            {
                LOGE("     Material should be a string pointing at material description");
                succeeded = false;
            }
            else
                LOGD("    \\_ " << o.value.GetString());
        }

        if (MODEL_MESH_VERTICES_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            succeeded = ValidateArrayOfCoords(o.value, o.name.GetString(), 3, vertCount);
        }

        if (MODEL_MESH_NORMALS_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            succeeded = ValidateArrayOfCoords(o.value, o.name.GetString(), 3, normalCount);
        }

        if (MODEL_MESH_TANGENTS_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            succeeded = ValidateArrayOfCoords(o.value, o.name.GetString(), 3, tangentCount);
        }

        if (MODEL_MESH_UVS_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            succeeded = ValidateArrayOfCoords(o.value, o.name.GetString(), 2, uvCount);
        }

        if (MODEL_MESH_INDICES_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            succeeded = ValidateIndices(o.value, maxInd);
        }
    }

    if (vertCount == 0 || normalCount == 0 || tangentCount == 0 || uvCount == 0 ||
        vertCount != normalCount || vertCount != tangentCount || vertCount != uvCount)
    {
        LOGE("   Mesh requires having a vertex, normal, tangent and UV arrays, " <<
             "each having the same number of elements!");
        succeeded = false;
    }

    if (static_cast<size_t>(maxInd) >= vertCount)
    {
        LOGE("   Invalid indices appear in indices array");
        succeeded = false;
    }

    return succeeded;
}

bool KrayoJSONModelFile::ValidateFile(const rapidjson::Value& node)
{
    if (!node.IsObject())
    {
        LOGE("Invalid object node");
        return false;
    }

    bool succeeded = true;
    LOGD("node member count " << node.GetObject().MemberCount());
    for (auto& o: node.GetObject())
    {
        LOGD("\\_ " << o.name.GetString());

        if (MODEL_NAME_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            if (!o.value.IsString())
            {
                LOGE("   Field " << o.name.GetString() << " should be a String object");
                succeeded = false;
            }
            else
                LOGD("  \\_ " << o.value.GetString());
        }

        if (MODEL_MESHES_NODE_NAME.compare(o.name.GetString()) == 0)
        {
            if (!o.value.IsArray())
            {
                LOGE("   Field " << o.name.GetString() << " should be an array of objects");
                succeeded = false;
            }

            if (o.value.GetArray().Size() == 0)
            {
                LOGE("   Field " << o.name.GetString() << " should have at least one object");
                succeeded = false;
            }

            if (!succeeded) break;

            const auto& meshArray = o.value.GetArray();
            for (uint32_t i = 0; i < meshArray.Size(); ++i)
            {
                if (!ValidateMesh(meshArray[i]))
                {
                    LOGE("   Failed to validate mesh #" << i);
                    succeeded = false;
                }
            }
        }
    }

    return succeeded;
}

bool KrayoJSONModelFile::ProbeFile(const std::string& path)
{
    if (path.rfind(".krayojson") == std::string::npos)
    {
        LOGI("Provided file does not have .krayojson extension");
        return false;
    }

    std::ifstream file(path);
    if (!file)
    {
        LOGI("KrayoJSON file failed to open");
        return false;
    }

    std::string fileString((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());

    rapidjson::Document fileJson;
    fileJson.Parse(fileString.c_str());

    if (fileJson.HasParseError())
    {
        LOGI("Unable to parse " << path << " JSON file");
        return false;
    }

    if (!fileJson.IsObject())
    {
        LOGI("Provided file " << path << " is not a readable JSON object");
        return false;
    }

    LOGI("Provided file " << path << " is a readable JSON object");
    return true;
}

bool KrayoJSONModelFile::Open(const std::string& path)
{
    std::ifstream file(path);
    if (!file)
    {
        LOGE("Cannot open KrayoJSON file to probe");
        return false;
    }

    std::string fileString((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());

    rapidjson::Document fileJson;
    fileJson.Parse(fileString.c_str());

    if (fileJson.HasParseError())
    {
        LOGI("Unable to parse " << path << " JSON file");
        return false;
    }

    if (!fileJson.IsObject())
    {
        LOGE("Provided file " << path << " is not a valid JSON object");
        return false;
    }

    LOGD("Analyzing and validating JSON file " << path << ":");
    if (!ValidateFile(fileJson.GetObject()))
    {
        LOGE("KrayoJSON file " << path << " is invalid or incomplete");
        return false;
    }

    LOGD("File correct, loading");
    fileJson.Parse(fileString.c_str());
    return LoadMeshes(fileJson.GetObject());
}

void KrayoJSONModelFile::Close()
{
}

} // namespace Utils
} // namespace Krayo
