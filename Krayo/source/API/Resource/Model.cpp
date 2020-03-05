#include "Krayo/Resource/Model.hpp"

#include "Resource/Model.hpp"


namespace Krayo {
namespace Resource {

Model::Model(const std::shared_ptr<Internal::Model>& model)
    : IResource(std::dynamic_pointer_cast<Internal::IResource>(model))
{
}

Model::~Model()
{
}

} // namespace Resource
} // namespace Krayo
