#pragma once

#include "Resource/IResource.hpp"

#include "Utils/ModelLoader.hpp"

#include <vector>
#include <functional>
#include <string>


namespace Krayo {
namespace Resource {
namespace Internal {

class Material: public ResourceBase<Material>
{
    lkCommon::Utils::PixelFloat4 mColor;

public:
    Material(const std::string& name);

    bool Load(const std::shared_ptr<Utils::IFileData>& file) override;

    LKCOMMON_INLINE const lkCommon::Utils::PixelFloat4& GetColor() const
    {
        return mColor;
    }
};

} // namespace Internal
} // namespace Resource
} // namespace Krayo
