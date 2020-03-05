#include "Manager.hpp"

#include "Resource/Model.hpp"
#include "Resource/Material.hpp"
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
std::shared_ptr<IResource> Manager::CreateResourceGeneric(ResourceContainer& c, const std::string& name)
{
    c.emplace_back(std::make_shared<T>(name));
    LOGD("Created Resource " << reinterpret_cast<void*>(c.back().get()));
    return c.back();
}

std::string Manager::GetModelNameFromPath(const std::string& path)
{
    using namespace lkCommon::System;
    std::string result = FS::GetFileName(path);

    std::size_t extPos = result.rfind('.');
    return result.substr(0, extPos);
}

std::shared_ptr<IResource> Manager::CreateResource(const Krayo::Resource::Type type, const std::string& name)
{
    LKCOMMON_ASSERT(static_cast<uint32_t>(type) < static_cast<uint32_t>(Resource::Type::Count),
                    "Resource Type invalid (out of range)");
    ResourceContainer& c = mResourceContainers[static_cast<size_t>(type)];

    switch (type)
    {
    case Type::Model:
        return CreateResourceGeneric<Model>(c, name);
    case Type::Material:
        return CreateResourceGeneric<Material>(c, name);
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

    for (auto& mat: file->GetMaterials())
    {
        std::shared_ptr<IResource> m = CreateResource(Type::Material, mat->GetName());
        if (!m)
        {
            LOGE("Failed to create new Material Resource " << mat->GetName());
        }

        if (!m->Load(mat))
        {
            LOGE("Failed to load Material " << mat->GetName());
            return false;
        }
    }

    std::shared_ptr<IResource> m = CreateResource(Type::Model, file->GetName());
    if (!m)
    {
        LOGE("Failed to create new Resource " << file->GetName());
        return false;
    }

    std::shared_ptr<Internal::Model> modelRes = std::dynamic_pointer_cast<Internal::Model>(m);
    if (!modelRes->Load(file))
    {
        LOGE("Failed to load Model resource from file " << path);
        return false;
    }

    LKCOMMON_ASSERT(modelRes->mMeshes.size() == file->GetMeshes().size(),
                    "Model Resource should have the same amount of meshes as FileModel");

    size_t meshCount = modelRes->mMeshes.size();
    for (uint32_t i = 0; i < meshCount; ++i)
    {
        Internal::Mesh& mesh = modelRes->mMeshes[i];
        const std::shared_ptr<Utils::FileMesh>& fileMesh = file->GetMeshes()[i];

        if (!fileMesh->GetMaterialName().empty())
        {
            mesh.material = std::dynamic_pointer_cast<Internal::Material>(
                GetResource(Type::Material, fileMesh->GetMaterialName())
            );

            if (!mesh.material)
            {
                LOGE("Failed to find matching Material resource to bind: " << fileMesh->GetMaterialName());
            }
        }
    }

    return true;
}

std::shared_ptr<Internal::IResource> Manager::GetResource(const Krayo::Resource::Type type, const std::string& name)
{
    LKCOMMON_ASSERT(static_cast<uint32_t>(type) < static_cast<uint32_t>(Resource::Type::Count),
                    "Resource Type invalid (out of range)");
    ResourceContainer& c = mResourceContainers[static_cast<size_t>(type)];

    for (const auto& res: c)
    {
        LOGD("  Searching for " << name << ": " << res->GetName());
        if (res->GetName() == name)
        {
            return res;
        }
    }

    return nullptr;
}

} // namespace Internal
} // namespace Resource
} // namespace Krayo
