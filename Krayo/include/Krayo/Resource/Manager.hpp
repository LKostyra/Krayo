#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include "Krayo/Resource/Model.hpp"

#include <string>


namespace Krayo {
namespace Resource {

class Manager final
{
    friend class Krayo::Engine;

    Internal::Manager& mImpl;

    Manager(Internal::Manager& manager);
    ~Manager() = default;

public:
    /**
     * Creates a Model resource in the Engine and returns it.
     *
     * @p[in] name Name of Model to create.
     * @return Created Model resource object. In case of error object will not
     *         be valid (can be checked with Model::IsValid() call)
     */
    KRAYO_API Model CreateModel(const std::string& name);

    /**
     * Gets a Model from Resource Manager.
     *
     * @p[in] name Name of Model to acquire
     * @return Acquired Model resource object. In case of not existing object,
     *         it will not be valid (which can be checked with Model::IsValid()
     *         call)
     */
    KRAYO_API Model GetModel(const std::string& name);
};

} // namespace Resource
} // namespace Krayo
