#include "Model.hpp"


namespace Krayo {
namespace Resources {

Model::Model(const std::string& name)
    : Resource(name)
{
}

bool Model::Load(const std::string& path)
{
    return false;
}

} // namespace Resources
} // namespace Krayo
