#include "Material.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Resource {
namespace Internal {

Material::Material(const std::string& name)
    : ResourceBase<Material>(name)
{
}

bool Material::Load(const std::shared_ptr<Utils::IFileData>& file)
{
    LKCOMMON_ASSERT(file->GetType() == Utils::FileDataType::Material, "Provided FileData pointer of invalid type");

    const std::shared_ptr<Utils::FileMaterial>& mat = std::dynamic_pointer_cast<Utils::FileMaterial>(file);

    mColor = mat->GetColor();

    return true;
}

} // namespace Internal
} // namespace Resource
} // namespace Krayo
