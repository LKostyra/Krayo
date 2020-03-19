#ifndef _KRAYO_INTERNAL_UTILS_CONTAINER_HPP_
#error "Include Container.hpp, not implementation header"
#endif // _KRAYO_INTERNAL_UTILS_CONTAINER_HPP_

#include "Container.hpp"

#include "Krayo/ApiDef.hpp"


namespace Krayo {
namespace Utils {

template <typename T, typename TID, size_t maxObjects>
Container<T, TID, maxObjects>::Container()
    : mObjectMemory(nullptr)
{
}

template <typename T, typename TID, size_t maxObjects>
TID Container<T, TID, maxObjects>::Create()
{
    LKCOMMON_ASSERT((mObjects.size() - mFreeObjects.Size()) < maxObjects,
                    "Reached max limit of available objects!");

    TID retID = KRAYO_INVALID_ID(TID);
    if (mFreeObjects.Size() != 0)
    {
        retID = mFreeObjects.Pop();
    }
    else
    {
        retID = mObjects.size();
        mObjects.emplace_back();
    }

    return retID;
}

template <typename T, typename TID, size_t maxObjects>
void Container<T, TID, maxObjects>::Delete(TID id)
{
    //T& obj =
    mFreeObjects.insert(id);
    return;
}

template <typename T, typename TID, size_t maxObjects>
T& Container<T, TID, maxObjects>::Get(TID id)
{
    return;
}

} // namespace Utils
} // namespace Krayo
