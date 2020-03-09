#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include "Krayo/Component/IComponent.hpp"


namespace Krayo {
namespace Component {

class Camera: public IComponent
{
    Camera(const std::shared_ptr<Internal::Camera>& cameraImpl);

public:
};

} // namespace Component
} // namespace Krayo
