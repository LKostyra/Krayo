#pragma once

#include "Krayo/Resource/Type.hpp"
#include "Krayo/Resource/IResource.hpp"

#include "Utils/ModelFile/IModelFile.hpp"
#include "Utils/TypeID.hpp"

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

    virtual bool Load(const std::unique_ptr<Utils::IModelFile>& file) = 0;
    virtual const uint32_t GetTypeID() const = 0;

    const std::string& GetName() const
    {
        return mName;
    }
};

template <typename T>
class ResourceBase: public IResource
{
    static const uint32_t mResourceTypeID;

public:
    ResourceBase(const std::string& name)
        : IResource(name)
    {
    }

    bool Load(const std::unique_ptr<Utils::IModelFile>& file)
    {
        return static_cast<T*>(this)->Load(file);
    }

    virtual const uint32_t GetTypeID() const override { return mResourceTypeID; }
};

template <typename T>
const uint32_t ResourceBase<T>::mResourceTypeID = Utils::TypeID<IResource>::Get<T>();

} // namespace Internal
} // namespace Resource
} // namespace Krayo
