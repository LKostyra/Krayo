#include "Object.hpp"


namespace Krayo {
namespace Scene {
namespace Internal {

Object::Object(const std::string& name)
    : mName(name)
    , mComponent(nullptr)
{
}

Object::~Object()
{
    mComponent = nullptr;
}

} // namespace Internal
} // namespace Scene
} // namespace Krayo
