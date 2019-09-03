#include "Krayo/Scene/Object.hpp"


namespace Krayo {
namespace Scene {

Object::Object(const std::shared_ptr<Internal::Object>& impl)
    : mImpl(impl)
{
}

} // namespace Scene
} // namespace Krayo
