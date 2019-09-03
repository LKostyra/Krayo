#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include <string>
#include <memory>


namespace Krayo {
namespace Resource {

class Model
{
    friend class Manager;

    std::shared_ptr<Internal::Model> mImpl;

    Model(const std::shared_ptr<Internal::Model>& impl);

public:
    KRAYO_API ~Model() = default;

    KRAYO_API bool Load(const std::string& path);
};

} // namespace Resource
} // namespace Krayo
