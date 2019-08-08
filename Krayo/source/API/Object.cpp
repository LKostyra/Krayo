#include "Krayo/Object.hpp"


namespace Krayo {

Object::Object(const std::string& name)
    : mName(name)
    , mComponent(nullptr)
{
}

} // namespace Krayo
