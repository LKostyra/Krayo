#pragma once

#include "Krayo/Resource/IResource.hpp"
#include "Krayo/Resource/Type.hpp"

#include <string>
#include <memory>
#include <vector>


namespace Krayo {
namespace Resource {

class Model final: public IResource
{
    friend class Krayo::Resource::Manager;
    friend class Krayo::Component::Model;

    Model(Internal::Model* impl);

public:
    KRAYO_API ~Model();

    Type GetType() const override
    {
        return Type::Model;
    }
};

} // namespace Resource
} // namespace Krayo
