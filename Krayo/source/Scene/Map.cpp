#include "Scene/Map.hpp"

#include <lkCommon/Utils/Logger.hpp>


namespace Krayo {
namespace Scene {
namespace Internal {

Map::Map(const std::string& name)
    : mName(name)
{
}

Map::~Map()
{
}

template <typename ItemType>
CreateResult<ItemType> Map::CreateItem(ResourceCollection<ItemType>& m, const std::string& name)
{
    auto res = m.emplace(std::make_pair(name, std::make_shared<ItemType>(name)));
    if (!res.second)
        return nullptr;

    return res.first->second;
}

template <typename ItemType>
void Map::ForEachItem(const ResourceCollection<ItemType>& m, Callback<ItemType>& func) const
{
    for (auto& it: m)
        if (!func(it.second.get()))
            return;
}

CreateResult<Internal::Object> Map::CreateObject(const std::string& name)
{
    return CreateItem<Internal::Object>(mObjects, name);
}

CreateResult<Internal::Component> Map::CreateComponent(Internal::ComponentType type, const std::string& name)
{
    switch (type)
    {
    case Internal::ComponentType::Model:
        return CreateItem<Model>(mModelComponents, name);
    case Internal::ComponentType::Light:
        return CreateItem<Light>(mLightComponents, name);
    case Internal::ComponentType::Emitter:
        return CreateItem<Emitter>(mEmitterComponents, name);
    default:
        LOGE("Unknown component type provided to create");
        return nullptr;
    }
}

void Map::ForEachLight(Callback<Light> func) const
{
    ForEachItem<Light>(mLightComponents, func);
}

void Map::ForEachEmitter(Callback<Emitter> func) const
{
    ForEachItem<Emitter>(mEmitterComponents, func);
}

void Map::ForEachObject(Callback<Object> func) const
{
    ForEachItem<Object>(mObjects, func);
}

} // namespace Internal
} // namespace Scene
} // namespace Krayo


/*
OLD INITIALIZATION CODE LOADING FBX FROM FILE

FbxFileTexture* Map::FileTextureFromMaterial(FbxSurfaceMaterial* material, const std::string& propertyName)
{
    FbxProperty prop = material->FindProperty(propertyName.c_str());
    if (!prop.IsValid())
    {
        LOGW("Material " << material->GetName() << " has no " << propertyName << " property");
        return nullptr;
    }

    FbxTexture* tex = prop.GetSrcObject<FbxTexture>(0);
    FbxFileTexture* texFile = FbxCast<FbxFileTexture>(tex);
    return texFile; // can return nullptr here if requested property does not exist
}

lkCommon::Utils::PixelFloat4 Map::ColorVector4FromMaterial(FbxSurfaceMaterial* material)
{
    if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
    {
        FbxPropertyT<FbxDouble3> color = reinterpret_cast<FbxSurfacePhong*>(material)->Diffuse;
        return lkCommon::Utils::PixelFloat4(static_cast<float>(color.Get()[0]), static_cast<float>(color.Get()[1]), static_cast<float>(color.Get()[2]), 1.0f);
    }

    return lkCommon::Utils::PixelFloat4(1.0f);
}

bool Map::Init(const std::string& fbxFile)
{
    if (!fbxFile.empty())
    {
        LOGD("Loading scene from FBX file");

        if (!mFBXFile.Open(fbxFile))
        {
            LOGE("Failed to open FBX scene file.");
            return false;
        }

        uint32_t counter = 0;
        mFBXFile.Traverse([&](FbxNode* node)
        {
            uint32_t attributeCount = node->GetNodeAttributeCount();

            for (uint32_t i = 0; i < attributeCount; ++i)
            {
                FbxNodeAttribute* attr = node->GetNodeAttributeByIndex(i);

                if (attr->GetAttributeType() == FbxNodeAttribute::eMesh)
                {
                    FbxMesh* mesh = reinterpret_cast<FbxMesh*>(attr);
                    if (!mesh->IsTriangleMesh())
                    {
                        LOGD("Mesh " << node->GetName() << " requires triangulation - converting, this might take some time.");
                        mFBXFile.GetConverter()->Triangulate(attr, true);
                    }

                    ModelDesc modelDesc;
                    modelDesc.mesh = mesh;
                    // Material loading
                    int32_t matCount = node->GetSrcObjectCount<FbxSurfaceMaterial>();
                    Material* mat = nullptr;
                    if (matCount > 0)
                    {
                        for (int32_t m = 0; m < matCount; ++m)
                        {
                            FbxSurfaceMaterial* material = node->GetSrcObject<FbxSurfaceMaterial>(m);
                            FbxFileTexture* diffTex = FileTextureFromMaterial(material, material->sDiffuse);
                            FbxFileTexture* normTex = FileTextureFromMaterial(material, material->sNormalMap);
                            FbxFileTexture* maskTex = FileTextureFromMaterial(material, material->sTransparencyFactor);

                            auto matResult = GetMaterial(material->GetName());
                            mat = matResult.first;
                            if (matResult.second)
                            {
                                // new material, initialize
                                MaterialDesc matDesc;
                                matDesc.color = ColorVector4FromMaterial(material);
                                if (diffTex) matDesc.diffusePath = diffTex->GetFileName();
                                if (normTex) matDesc.normalPath = normTex->GetFileName();
                                if (maskTex) matDesc.maskPath = maskTex->GetFileName();
                                if (!mat->Init(matDesc))
                                {
                                    LOGE("Failed to initialize material for mesh " << node->GetName());
                                    mat = nullptr;
                                }
                            }

                            modelDesc.materials.push_back(mat);
                        }
                    }

                    Object* o = CreateObject();
                    auto mResult = GetComponent(ComponentType::Model, node->GetName());
                    Model* m = dynamic_cast<Model*>(mResult.first);
                    if (mResult.second)
                    {
                        m->Init(modelDesc);
                        m->SetScale(static_cast<float>(node->LclScaling.Get()[0]),
                                    static_cast<float>(node->LclScaling.Get()[1]),
                                    static_cast<float>(node->LclScaling.Get()[2]));
                        m->SetPosition(static_cast<float>(node->LclTranslation.Get()[0]),
                                       static_cast<float>(node->LclTranslation.Get()[1]),
                                       static_cast<float>(node->LclTranslation.Get()[2]));
                    }

                    o->SetComponent(m);
                    counter += matCount;
                }
            }
        });

        LOGD("Counted " << counter << " objects in scene " << fbxFile);
    }
    else
        LOGI("Initialized empty scene");

    return true;
}
*/
