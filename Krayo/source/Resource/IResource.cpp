#include "IResource.hpp"


namespace Krayo {
namespace Resource {
namespace Internal {

IResource::IResource(const std::string& name)
    : mName(name)
{
}

IResource::~IResource()
{
}

} // namespace Internal
} // namespace Resource
} // namespace Krayo
