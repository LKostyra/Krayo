#pragma once

#include "Krayo/Resource/Type.hpp"

#include <string>


namespace Krayo {
namespace Resource {
namespace Internal {

class IResource
{
    std::string mName;

public:
    IResource(const std::string& name);
    virtual ~IResource();

    virtual bool Load(const std::string& path) = 0;
    virtual Krayo::Resource::Type GetType() const = 0;
};

} // namespace Internal
} // namespace Resource
} // namespace Krayo
