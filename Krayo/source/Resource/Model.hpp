#pragma once

#include <lkCommon/lkCommon.hpp>

#include "IResource.hpp"


namespace Krayo {
namespace Resource {
namespace Internal {

class Model: public IResource
{
public:
    Model(const std::string& name);

    bool Load(const std::string& path) override;

    LKCOMMON_INLINE Krayo::Resource::Type GetType() const
    {
        return Krayo::Resource::Type::Model;
    }
};

} // namespace Internal
} // namespace Resource
} // namespace Krayo
