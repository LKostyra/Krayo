#include "Krayo/Resource/Model.hpp"

#include "Resource/Model.hpp"


namespace Krayo {
namespace Resource {

Model::Model(Internal::Model* model)
    : IResource(model)
{
}

Model::~Model()
{
}

} // namespace Resource
} // namespace Krayo
