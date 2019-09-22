#pragma once

#include <cstdint>


namespace Krayo {
namespace Utils {

template <typename Family>
class TypeID
{
    static uint32_t mCounter;

public:
    template <typename T>
    static const uint32_t Get()
    {
        static const uint32_t id = mCounter++;
        return id;
    }

    static const uint32_t Count()
    {
        return mCounter;
    }
};

} // namespace Utils
} // namespace Krayo
