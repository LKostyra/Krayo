#include "Krayo/Resource/IResource.hpp"

#include "Resource/IResource.hpp"


namespace Krayo {
namespace Resource {

IResource::IResource(const std::shared_ptr<Internal::IResource>& impl)
    : mImpl(impl)
{
}

} // namespace Resource
} // namespace Krayo
