#include "Scene/Camera.hpp"


namespace Krayo {
namespace Scene {

Camera::Camera()
    : mCurrentDesc(0)
    , mNewDesc(1)
    , mCameraDescs{}
{
}

void Camera::Update(const CameraDesc& desc)
{
    mCameraDescs[mCurrentDesc] = desc;
    std::swap(mCurrentDesc, mNewDesc);
}

} // namespace Scene
} // namespace Krayo
