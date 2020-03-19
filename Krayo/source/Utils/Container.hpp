#pragma once
#define _KRAYO_INTERNAL_UTILS_CONTAINER_HPP_

#include <vector>
#include <unordered_set>

#include <lkCommon/Utils/StaticStack.hpp>
#include <lkCommon/Allocators/ArenaAllocator.hpp>


namespace Krayo {
namespace Utils {

template <typename T, typename TID, size_t maxObjects>
class Container
{
    using namespace lkCommon::Allocators;
    using FreeSlotsContainer = lkCommon::Utils::StaticStack<TID, maxObjects>;

    Memory<ArenaAllocator> mObjectMemory;

    Container();

public:
    TID Create();
    void Delete(TID id);
    T& Get(TID id);
};

} // namespace Utils
} // namespace Krayo

#include "ContainerImpl.hpp"
