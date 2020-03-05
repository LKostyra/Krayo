#pragma once

#include "Krayo/ApiDef.hpp"
#include "Krayo/ApiPrerequisites.hpp"

#include "Krayo/Resource/Type.hpp"

#include <string>
#include <memory>


namespace Krayo {
namespace Resource {

class IResource
{
protected:
    std::shared_ptr<Internal::IResource> mImpl;

    IResource(const std::shared_ptr<Internal::IResource>& impl);

public:
    virtual Type GetType() const = 0;

    operator bool()
    {
        return mImpl != nullptr;
    }
};

} // namespace Resource
} // namespace Krayo
