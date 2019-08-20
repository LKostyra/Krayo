#pragma once

#include <lkCommon/lkCommon.hpp>

#include "Resource.hpp"


namespace Krayo {
namespace Resources {

class Model: public Resource
{
public:
    Model(const std::string& name);

    bool Load(const std::string& path) override;

    LKCOMMON_INLINE ResourceType GetType() const
    {
        return ResourceType::Model;
    }
};

} // namespace Resources
} // namespace Krayo
