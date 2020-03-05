#pragma once

#include "Resource/IResource.hpp"

#include "Utils/ModelLoader.hpp"

#include <vector>
#include <functional>
#include <string>


namespace Krayo {
namespace Resource {
namespace Internal {

class Texture: public ResourceBase<Texture>
{

public:
    Texture(const std::string& name);

    bool Load(const std::shared_ptr<Utils::IFileData>& file) override;
};

} // namespace Internal
} // namespace Resource
} // namespace Krayo
