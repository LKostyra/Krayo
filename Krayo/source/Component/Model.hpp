#pragma once

#include "Component/IComponent.hpp"

#include "Resource/Model.hpp"


namespace Krayo {
namespace Component {
namespace Internal {

class Model: public ComponentBase<Model>
{
    Resource::Internal::Model* mModelResource;

public:
    Model(const std::string& name);

    void AttachResource(Resource::Internal::Model* modelRes);
    Resource::Internal::Model* GetResource() const;
};

} // namespace Internal
} // namespace Component
} // namespace Krayo
