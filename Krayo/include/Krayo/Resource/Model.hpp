#pragma once

#include "Krayo/Resource/IResource.hpp"

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

    KRAYO_API bool Load(const std::string& path);
};

} // namespace Resource
} // namespace Krayo
