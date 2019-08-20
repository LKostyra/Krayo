#pragma once

#include <string>


namespace Krayo {
namespace Resources {

enum class ResourceType: unsigned char
{
    Model,
    Texture,
    Material,
};

class Resource
{
    std::string mName;

public:
    Resource(const std::string& name);
    virtual ~Resource();

    virtual bool Load(const std::string& path) = 0;
    virtual ResourceType GetType() const = 0;
};

} // namespace Resources
} // namespace Krayo
