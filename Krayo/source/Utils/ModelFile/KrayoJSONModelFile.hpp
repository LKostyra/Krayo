#pragma once

#include "IModelFile.hpp"

#include <rapidjson/document.h>
#include <lkCommon/lkCommon.hpp>


namespace Krayo {
namespace Utils {

class KrayoJSONModelFile: public IModelFile
{
    bool mIsOpened;
    std::vector<std::string> mReadMaterialNames; // for validation

    bool InitializeMaterial(const rapidjson::Value& node, FileMaterial& material);
    bool LoadMaterial(const rapidjson::Value& node, FileMaterial& material);

    bool InitializeMesh(const rapidjson::Value& node, FileMesh& mesh);
    bool LoadVertices(const rapidjson::Value& node, FileMesh& mesh);
    bool LoadNormals(const rapidjson::Value& node, FileMesh& mesh);
    bool LoadTangents(const rapidjson::Value& node, FileMesh& mesh);
    bool LoadUVs(const rapidjson::Value& node, FileMesh& mesh);
    bool LoadIndices(const rapidjson::Value& node, FileMesh& mesh);
    bool LoadMesh(const rapidjson::Value& node, FileMesh& mesh);

    bool LoadFile(const rapidjson::Value& node);


    bool ValidateArrayOfCoords(const rapidjson::Value& node, const char* name,
                               size_t dimensions, size_t& elements);
    bool ValidateFloatArray(const rapidjson::Value& node, const char* name, size_t minSize);
    bool ValidateFilePath(const rapidjson::Value& node, const char* name);
    bool ValidateIndices(const rapidjson::Value& node, uint32_t& maxInd);

    bool ValidateMaterial(const rapidjson::Value& node);
    bool ValidateMesh(const rapidjson::Value& node);
    bool ValidateFile(const rapidjson::Value& node);

public:
    KrayoJSONModelFile();
    ~KrayoJSONModelFile();

    static bool ProbeFile(const std::string& path);

    bool Open(const std::string& path) override;
    void Close();

    operator bool() const
    {
        return IsOpened();
    }

    LKCOMMON_INLINE bool IsOpened() const
    {
        return mIsOpened;
    }

    LKCOMMON_INLINE ModelFileType GetType() const override
    {
        return ModelFileType::KrayoJSON;
    }
};

} // namespace Utils
} // namespace Krayo
