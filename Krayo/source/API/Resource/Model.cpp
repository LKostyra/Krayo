#include "Krayo/Resource/Model.hpp"

#include "Resource/Model.hpp"


namespace Krayo {
namespace Resource {

Model::Model(const std::shared_ptr<Internal::Model>& impl)
    : mImpl(impl)
{
}

bool Model::Load(const std::string& path)
{
    return mImpl->Load(path);
}

} // namespace Krayo
} // namespace Resource
