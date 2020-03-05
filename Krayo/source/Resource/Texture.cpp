#include "Texture.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Resource {
namespace Internal {

Texture::Texture(const std::string& name)
    : ResourceBase<Texture>(name)
{
}

bool Texture::Load(const std::shared_ptr<Utils::IFileData>& file)
{
    return true;
}

} // namespace Internal
} // namespace Resource
} // namespace Krayo
