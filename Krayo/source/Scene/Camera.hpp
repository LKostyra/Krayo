#pragma once

#include <lkCommon/lkCommon.hpp>
#include <lkCommon/Math/Vector4.hpp>
#include <lkCommon/Math/Matrix4.hpp>
#include <lkCommon/Math/Utilities.hpp>

#include "Math/Frustum.hpp"


namespace Krayo {
namespace Scene {
namespace Internal {

enum class CameraMode: unsigned char
{
    FREEROAM = 0,
    TRACED
};

struct CameraDesc
{
    lkCommon::Math::Vector4 pos;
    lkCommon::Math::Vector4 at;
    lkCommon::Math::Vector4 up;
};

class Camera final
{
    uint32_t mCurrentDesc;
    uint32_t mNewDesc;
    CameraDesc mCameraDescs[2];

public:
    Camera();

    void Update(const CameraDesc& desc);

    LKCOMMON_INLINE lkCommon::Math::Vector4 GetPosition(float interpolation) const
    {
        return lkCommon::Math::Util::Lerp(mCameraDescs[mCurrentDesc].pos, mCameraDescs[mNewDesc].pos, interpolation);
    }

    LKCOMMON_INLINE lkCommon::Math::Vector4 GetAtPosition(float interpolation) const
    {
        return lkCommon::Math::Util::Lerp(mCameraDescs[mCurrentDesc].at, mCameraDescs[mNewDesc].at, interpolation);
    }

    LKCOMMON_INLINE lkCommon::Math::Vector4 GetUpVector(float interpolation) const
    {
        return lkCommon::Math::Util::Lerp(mCameraDescs[mCurrentDesc].up, mCameraDescs[mNewDesc].up, interpolation);
    }

    LKCOMMON_INLINE lkCommon::Math::Matrix4 GetView(float interpolation) const
    {
        return lkCommon::Math::Matrix4::CreateRHLookAt(
            GetPosition(interpolation), GetAtPosition(interpolation), GetUpVector(interpolation)
        );
    }
};

} // namespace Internal
} // namespace Scene
} // namespace Krayo
