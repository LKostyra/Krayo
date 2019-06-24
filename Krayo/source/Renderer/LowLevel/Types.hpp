#pragma once

namespace Krayo {
namespace Renderer {

enum DeviceQueueType
{
    GRAPHICS = 0,
    TRANSFER,
    COMPUTE,
    COUNT
};

enum ClearType
{
    NONE = 0,
    COLOR,
    DEPTH,
    ALL = COLOR | DEPTH,
};

} // namespace Renderer
} // namespace Krayo
