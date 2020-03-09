#pragma once


namespace Krayo {
namespace Component {

enum class Type: unsigned char
{
    Model = 0,
    Transform,
    Camera,
    //Light,
    //Emitter,
    Count
};

} // namespace Component
} // namespace Krayo
