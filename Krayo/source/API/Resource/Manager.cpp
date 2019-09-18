#include "Krayo/Resource/Manager.hpp"

#include "Resource/Manager.hpp"


namespace Krayo {
namespace Resource {

Manager::Manager(Internal::Manager& manager)
    : mImpl(manager)
{
}

} // namespace Resource
} // namespace Krayo
