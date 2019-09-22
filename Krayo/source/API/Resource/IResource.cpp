#include "Krayo/Resource/IResource.hpp"

#include "Resource/IResource.hpp"


namespace Krayo {
namespace Resource {

IResource::IResource(Internal::IResource* impl)
    : mImpl(impl)
{
}

} // namespace Resource
} // namespace Krayo
