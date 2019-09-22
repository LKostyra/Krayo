#pragma once

#include "Krayo/Component/IComponent.hpp"


namespace Krayo {
namespace Component {

class Model final: public IComponent
{
    friend class Krayo::Map;

    Model(Internal::Model* impl);

public:
    KRAYO_API ~Model();

    KRAYO_API void AttachResource(Resource::Model* modelRes);
};

} // namespace Component
} // namespace Krayo
