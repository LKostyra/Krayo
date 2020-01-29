#pragma once

#include "IModelFile.hpp"

#include <lkCommon/lkCommon.hpp>


namespace Krayo {
namespace Utils {

class OBJModelFile: public IModelFile
{
    bool mIsOpened;

public:
    OBJModelFile();
    ~OBJModelFile();

    static bool ProbeFile(const std::string& path);

    bool Open(const std::string& path) override;
    uint32_t GetMeshCount() const override;
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
        return ModelFileType::OBJ;
    }
};

} // namespace Utils
} // namespace Krayo
