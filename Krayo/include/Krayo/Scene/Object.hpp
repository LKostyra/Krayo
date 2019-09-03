#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include <memory>


namespace Krayo {
namespace Scene {

class Object final
{
    friend class Krayo::Scene::Map;

    std::shared_ptr<Internal::Object> mImpl;

    Object(const std::shared_ptr<Internal::Object>& impl);

public:
    KRAYO_API ~Object() = default;
};

} // namespace Scene
} // namespace Krayo
