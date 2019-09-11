#include "Mesh.hpp"

#include <lkCommon/lkCommon.hpp>
#include <lkCommon/Utils/Logger.hpp>

using namespace Krayo::Renderer;


namespace Krayo {
namespace Component {
namespace Internal {

Mesh::Mesh()
    : mPointCount(0)
    , mMaterial(nullptr)
    , mByIndices(false)
{
}

bool Mesh::InitBuffers(const std::vector<Vertex>& vertices,
                       const std::vector<VertexParams>& vertexParams,
                       int* indices, int indexCount)
{
    BufferDesc vbDesc;
    vbDesc.data = vertices.data();
    vbDesc.dataSize = vertices.size() * sizeof(Vertex);
    vbDesc.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    vbDesc.type = BufferType::Static;
    mVertexBuffer = ResourceFactory::Instance().CreateBuffer(vbDesc);
    if (!mVertexBuffer)
        return false;

    vbDesc.data = vertexParams.data();
    vbDesc.dataSize = vertexParams.size() * sizeof(VertexParams);
    mVertexParamsBuffer = ResourceFactory::Instance().CreateBuffer(vbDesc);
    if (!mVertexParamsBuffer)
        return false;

    mByIndices = false;
    mPointCount = static_cast<uint32_t>(vertices.size());

    if (indices && indexCount > 0)
    {
        BufferDesc ibDesc;
        ibDesc.data = indices;
        ibDesc.dataSize = indexCount * sizeof(uint32_t);
        ibDesc.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        ibDesc.type = BufferType::Static;
        mIndexBuffer = ResourceFactory::Instance().CreateBuffer(ibDesc);
        if (!mIndexBuffer)
            return false;

        mByIndices = true;
        mPointCount = indexCount;
    }

    return true;
}

bool Mesh::InitDefault()
{
    std::vector<Vertex> vertices
    {
        // front
        { { -0.5f,-0.5f, 0.5f } }, // 0        7----6
        { {  0.5f,-0.5f, 0.5f } }, // 1      3----2 |
        { {  0.5f, 0.5f, 0.5f } }, // 2      | 4--|-5
        { { -0.5f, 0.5f, 0.5f } }, // 3      0----1

        { { -0.5f,-0.5f,-0.5f } }, // 4
        { {  0.5f,-0.5f,-0.5f } }, // 5
        { {  0.5f, 0.5f,-0.5f } }, // 6
        { { -0.5f, 0.5f,-0.5f } }, // 7

        // side
        { { -0.5f,-0.5f,-0.5f } }, // 4
        { { -0.5f,-0.5f, 0.5f } }, // 0
        { { -0.5f, 0.5f, 0.5f } }, // 3
        { { -0.5f, 0.5f,-0.5f } }, // 7

        { {  0.5f,-0.5f, 0.5f } }, // 1
        { {  0.5f,-0.5f,-0.5f } }, // 5
        { {  0.5f, 0.5f,-0.5f } }, // 6
        { {  0.5f, 0.5f, 0.5f } }, // 2

        // top
        { { -0.5f, 0.5f, 0.5f } }, // 3
        { {  0.5f, 0.5f, 0.5f } }, // 2
        { {  0.5f, 0.5f,-0.5f } }, // 6
        { { -0.5f, 0.5f,-0.5f } }, // 7

        { { -0.5f,-0.5f,-0.5f } }, // 4
        { {  0.5f,-0.5f,-0.5f } }, // 5
        { {  0.5f,-0.5f, 0.5f } }, // 1
        { { -0.5f,-0.5f, 0.5f } }, // 0
    };

    std::vector<VertexParams> vertexParams
    {
        // front
        { {  0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } }, // 0        7----6
        { {  0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } }, // 1      3----2 |
        { {  0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } }, // 2      | 4--|-5
        { {  0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } }, // 3      0----1

        { {  0.0f, 0.0f,-1.0f }, { 0.0f, 1.0f } }, // 4
        { {  0.0f, 0.0f,-1.0f }, { 1.0f, 1.0f } }, // 5
        { {  0.0f, 0.0f,-1.0f }, { 1.0f, 0.0f } }, // 6
        { {  0.0f, 0.0f,-1.0f }, { 0.0f, 0.0f } }, // 7

        // side
        { { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } }, // 4
        { { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } }, // 0
        { { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } }, // 3
        { { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } }, // 7

        { {  1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } }, // 1
        { {  1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } }, // 5
        { {  1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } }, // 6
        { {  1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } }, // 2

        // top
        { {  0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } }, // 3
        { {  0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } }, // 2
        { {  0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }, // 6
        { {  0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } }, // 7

        { {  0.0f,-1.0f, 0.0f }, { 0.0f, 1.0f } }, // 4
        { {  0.0f,-1.0f, 0.0f }, { 1.0f, 1.0f } }, // 5
        { {  0.0f,-1.0f, 0.0f }, { 1.0f, 0.0f } }, // 1
        { {  0.0f,-1.0f, 0.0f }, { 0.0f, 0.0f } }, // 0
    };

    std::vector<int> indices
    {
        0, 1, 2, 0, 2, 3, // front
        7, 6, 5, 7, 5, 4, // back
        8, 9,10, 8,10,11, // left
       12,13,14,12,14,15, // right
       16,17,18,16,18,19, // top
       20,21,22,20,22,23, // bottom
    };

    return InitBuffers(vertices, vertexParams, indices.data(), static_cast<int>(indices.size()));
}

bool Mesh::Init()
{
    return InitDefault();
}

} // namespace Internal
} // namespace Component
} // namespace Krayo

/*
OLD IMPLEMENTATION OF INIT FROM FBX

bool Mesh::HasNormalMap(FbxMesh* mesh, int materialIndex)
{
    FbxNode* node = mesh->GetNode();
    FbxSurfaceMaterial* material = node->GetSrcObject<FbxSurfaceMaterial>(materialIndex);
    FbxProperty prop = material->FindProperty(material->sNormalMap);
    if (!prop.IsValid())
        return false;

    return (prop.GetSrcObjectCount<FbxTexture>() > 0);
}

bool Mesh::InitFromFBX(FbxMesh* mesh, int materialIndex)
{
    // find UV layer
    FbxLayerElementUV* uvs = nullptr;
    int uvLayer = 0;
    for (uvLayer = 0; uvLayer < mesh->GetLayerCount(); ++uvLayer)
    {
        uvs = mesh->GetLayer(uvLayer)->GetUVs();
        if (uvs)
            break;
    }

    if (!uvs)
    {
        LOGE("Mesh has no UVs generated!");
        return false;
    }

    if (uvs->GetMappingMode() != FbxLayerElement::eByPolygonVertex)
        LOGW("UVs are not generated on per-vertex basis.");

    // find normal layer
    FbxLayerElementNormal* normals = nullptr;
    for (int l = 0; l < mesh->GetLayerCount(); ++l)
    {
        normals = mesh->GetLayer(l)->GetNormals();
        if (normals)
            break;
    }

    if (!normals)
    {
        LOGE("Mesh has no normals generated!");
        return false;
    }

    // generate tangent data if mesh has normal map
    FbxLayerElementTangent* tangents = nullptr;
    if (HasNormalMap(mesh, materialIndex))
    {
        mesh->GenerateTangentsData(uvLayer, false);
        tangents = mesh->GetElementTangent(0);
    }

    // TODO there's an assumption that meshes have only one element material, fix it if needed
    FbxGeometryElementMaterial* matElement = mesh->GetElementMaterial(0);
    if (!matElement)
    {
        LOGW("Mesh " << mesh->GetName() << " has no material element - cannot extract control points per material.");
    }

    FbxLayerElement::EMappingMode matMapping = matElement->GetMappingMode();

    // left for debugging purposes, just in case
    // const char* lMappingTypes[] = { "None", "By Control Point", "By Polygon Vertex", "By Polygon", "By Edge", "All Same" };
    // const char* lReferenceMode[] = { "Direct", "Index", "Index to Direct"};

    std::vector<Vertex> vertices;
    std::vector<VertexParams> vertexParams;
    Vertex vert;
    VertexParams vertParams;
    LKCOMMON_ZERO_MEMORY(vert);

    FbxVector4 normalVec;
    for (int i = 0; i < mesh->GetPolygonCount(); ++i)
    {
        if (matMapping == FbxLayerElement::EMappingMode::eAllSame ||
           (matMapping == FbxLayerElement::EMappingMode::eByPolygon && matElement->GetIndexArray()[i] == materialIndex))
        {
            for (int j = 0; j < mesh->GetPolygonSize(i); ++j)
            {
                int p = mesh->GetPolygonVertex(i, j);
                int uv = mesh->GetTextureUVIndex(i, j);
                mesh->GetPolygonVertexNormal(i, j, normalVec);

                vert.pos[0] = static_cast<float>(mesh->GetControlPoints()[p].Buffer()[0]);
                vert.pos[1] = static_cast<float>(mesh->GetControlPoints()[p].Buffer()[1]);
                vert.pos[2] = static_cast<float>(mesh->GetControlPoints()[p].Buffer()[2]);
                vertParams.norm[0] = static_cast<float>(normalVec[0]);
                vertParams.norm[1] = static_cast<float>(normalVec[1]);
                vertParams.norm[2] = static_cast<float>(normalVec[2]);
                vertParams.uv[0] = static_cast<float>(uvs->GetDirectArray()[uv].Buffer()[0]);
                vertParams.uv[1] = static_cast<float>(uvs->GetDirectArray()[uv].Buffer()[1]);

                if (tangents)
                {
                    vertParams.tang[0] = static_cast<float>(tangents->GetDirectArray().GetAt((i*mesh->GetPolygonSize(i))+j).Buffer()[0]);
                    vertParams.tang[1] = static_cast<float>(tangents->GetDirectArray().GetAt((i*mesh->GetPolygonSize(i))+j).Buffer()[1]);
                    vertParams.tang[2] = static_cast<float>(tangents->GetDirectArray().GetAt((i*mesh->GetPolygonSize(i))+j).Buffer()[2]);
                }
                else
                {
                    vertParams.tang[0] = 0.0f;
                    vertParams.tang[1] = 0.0f;
                    vertParams.tang[2] = 0.0f;
                }

                vertices.push_back(vert);
                vertexParams.push_back(vertParams);
            }
        }
    }

    return InitBuffers(vertices, vertexParams, nullptr, 0);
}
*/
