#include "Manager.hpp"

#include "Resource/Model.hpp"
#include "Utils/TypeID.hpp"
#include "Utils/ModelLoader.hpp"
#include "Utils/ModelFile/IModelFile.hpp"

#include <lkCommon/lkCommon.hpp>
#include <lkCommon/Utils/Logger.hpp>
#include <lkCommon/System/FS.hpp>


namespace Krayo {
namespace Resource {
namespace Internal {


Manager::Manager()
    : mResourceContainers(Utils::TypeID<IResource>::Count())
{
    LOGD("Resource Container: " << mResourceContainers.size());
}

template <typename T>
IResource* Manager::CreateResourceGeneric(ResourceContainer& c, const std::string& name)
{
    c.emplace_back(std::make_shared<T>(name));
    LOGD("Created Resource " << reinterpret_cast<void*>(c.back().get()));
    return c.back().get();
}

std::string Manager::GetModelNameFromPath(const std::string& path)
{
    using namespace lkCommon::System;
    std::string result = FS::GetFileName(path);

    std::size_t extPos = result.rfind('.');
    return result.substr(0, extPos);
}

IResource* Manager::CreateResource(const Krayo::Resource::Type type, const std::string& name)
{
    LKCOMMON_ASSERT(static_cast<uint32_t>(type) < static_cast<uint32_t>(Resource::Type::Count),
                    "Resource Type invalid (out of range)");
    ResourceContainer& c = mResourceContainers[static_cast<size_t>(type)];

    switch (type)
    {
    case Type::Model:
        return CreateResourceGeneric<Model>(c, name);
    default:
        LOGE("Unknown resource type to create");
        return nullptr;
    }
}

bool Manager::LoadFile(const std::string& path)
{
    std::unique_ptr<Utils::IModelFile> file = Utils::ModelLoader::Open(path);
    if (!file)
    {
        LOGE("Failed to open file " << path);
        return false;
    }

    IResource* m = CreateResource(Type::Model, file->GetName());
    if (m == nullptr)
    {
        LOGE("Failed to create new Resource " << file->GetName());
        return false;
    }

    if (!m->Load(file))
    {
        LOGE("Failed to load Model resource from file " << path);
        return false;
    }

    return true;
}

Internal::IResource* Manager::GetResource(const Krayo::Resource::Type type, const std::string& name)
{
    LKCOMMON_ASSERT(static_cast<uint32_t>(type) < static_cast<uint32_t>(Resource::Type::Count),
                    "Resource Type invalid (out of range)");
    ResourceContainer& c = mResourceContainers[static_cast<size_t>(type)];

    IResource* r = nullptr;
    for (const auto& res: c)
    {
        if (res->GetName() == name)
        {
            r = res.get();
            break;
        }
    }

    return r;
}

} // namespace Internal
} // namespace Resource
} // namespace Krayo
