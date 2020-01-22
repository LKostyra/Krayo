#pragma once

#include "Component/IComponent.hpp"

#include <lkCommon/Math/Matrix4.hpp>


namespace Krayo {
namespace Component {
namespace Internal {

class Transform: public ComponentBase<Transform>
{
    lkCommon::Math::Matrix4 mTransform;

public:
    Transform(const std::string& name);

    LKCOMMON_INLINE const lkCommon::Math::Matrix4& Get() const
    {
        return mTransform;
    }
};

} // namespace Internal
} // namespace Component
} // namespace Krayo
