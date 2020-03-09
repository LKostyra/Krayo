#pragma once

#include "Krayo/Component/IComponent.hpp"


namespace Krayo {
namespace Component {

class Transform final: public IComponent
{
    friend class Krayo::Map;

    Transform(const std::shared_ptr<Internal::Transform>& impl);

public:
    KRAYO_API ~Transform();
};

} // namespace Component
} // namespace Krayo
