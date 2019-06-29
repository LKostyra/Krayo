#include <Krayo/Engine.hpp>


int main(int argc, char* argv[])
{
    bool debug = false;

#ifdef _DEBUG
    debug = true;
#endif

    Krayo::EngineDesc engineDesc;
    engineDesc.debug = debug;
    engineDesc.debugVerbose = true;
    engineDesc.vsync = false;
    engineDesc.windowWidth = 1280;
    engineDesc.windowHeight = 720;
    Krayo::Engine engine;
    if (!engine.Init(engineDesc))
    {
        return 1;
    }

    engine.MainLoop();

    return 0;
}



// OLD PARAMETERS USED TO RENDER SCENES
/*
const uint32_t windowWidth = 1280;
const uint32_t windowWidth = 720;

const int32_t EMITTERS_LIMIT = 1;
Krayo::Scene::Emitter* gEmitters[EMITTERS_LIMIT * 2 + 1];

const float LIGHT_AREA_X = 30.0f;
const float LIGHT_AREA_Y = 0.0f;
const float LIGHT_AREA_Z = 15.0f;
std::vector<Krayo::Scene::Light*> gLights;

uint32_t EMITTERS_PARTICLE_LIMIT = 128;
uint32_t LIGHT_COUNT = 128;
*/


// OLD WINDOW IMPLEMENTATION DERIVED FROM LKCOMMON'S WINDOW
/*
class GameWindow: public lkCommon::System::Window
{
    //Krayo::Scene::Camera mCamera;

    float mAngleX = -LKCOMMON_PIF * 0.3f;
    float mAngleY = -LKCOMMON_PIF * 0.2f;

    float mCameraAnimMoment = 0.0f;

    uint32_t mFrameCounter = 0;

    void OnUpdate(float deltaTime) override
    {
        lkCommon::Math::Vector4 newPos;
        lkCommon::Math::Vector4 updateDir;

        lkCommon::Math::Vector4 cameraFrontDir = mCamera.GetAtPosition() - mCamera.GetPosition();
        cameraFrontDir.Normalize();
        lkCommon::Math::Vector4 cameraRightDir = cameraFrontDir.Cross(mCamera.GetUpVector());
        lkCommon::Math::Vector4 cameraUpDir = cameraRightDir.Cross(cameraFrontDir);

        if (IsKeyPressed(lkCommon::System::KeyCode::W)) newPos += cameraFrontDir;
        if (IsKeyPressed(lkCommon::System::KeyCode::S)) newPos -= cameraFrontDir;
        if (IsKeyPressed(lkCommon::System::KeyCode::D)) newPos += cameraRightDir;
        if (IsKeyPressed(lkCommon::System::KeyCode::A)) newPos -= cameraRightDir;
        if (IsKeyPressed(lkCommon::System::KeyCode::R)) newPos -= cameraUpDir;
        if (IsKeyPressed(lkCommon::System::KeyCode::F)) newPos += cameraUpDir;

        float speed = 5.0f;
        newPos *= speed * deltaTime;

        // new direction
        updateDir = lkCommon::Math::Matrix4::CreateRotationX(mAngleY) * lkCommon::Math::Vector4(0.0f, 0.0f, 1.0f, 0.0f);
        updateDir = lkCommon::Math::Matrix4::CreateRotationY(mAngleX) * updateDir;
        updateDir.Normalize();

        Krayo::Scene::CameraDesc desc;
        desc.pos = mCamera.GetPosition() + newPos;
        desc.at = desc.pos + updateDir;
        desc.up = mCamera.GetUpVector();
        mCamera.Update(desc);
    }

    void OnMouseMove(uint32_t x, uint32_t y, int deltaX, int deltaY) override
    {
        LKCOMMON_UNUSED(x);
        LKCOMMON_UNUSED(y);

        if (IsMouseKeyPressed(0))
        {
            mAngleX -= deltaX * 0.005f;
            mAngleY -= deltaY * 0.005f;
        }
    }

    void OnKeyDown(lkCommon::System::KeyCode key) override
    {
    }
};
*/


// OLD API USE EXAMPLE
/*
    auto matResult = scene.GetMaterial("boxMaterial");
    Krayo::Scene::Material* boxMat = matResult.first;
    if (matResult.second)
    {
        Krayo::Scene::MaterialDesc matDesc;
        matDesc.diffusePath = lkCommon::System::FS::JoinPaths(Krayo::ResourceDir::TEXTURES, "Wood_Box_Diffuse.jpg");
        if (!boxMat->Init(matDesc))
        {
            LOGE("Failed to initialize material");
            return -1;
        }
    }

    matResult = scene.GetMaterial("boxMaterial2");
    Krayo::Scene::Material* boxMatNoTex = matResult.first;
    if (matResult.second)
    {
        Krayo::Scene::MaterialDesc matDesc;
        matDesc.color = lkCommon::Utils::PixelFloat4(0.2f, 0.4f, 0.9f, 1.0f);
        if (!boxMatNoTex->Init(matDesc))
        {
            LOGE("Failed to initialize no tex material");
            return -1;
        }
    }

    Krayo::Scene::ModelDesc modelDesc;
    modelDesc.materials.push_back(boxMat);
    /*
    // textured cube
    auto modelResult = scene.GetComponent(Krayo::Scene::ComponentType::Model, "box1");
    Krayo::Scene::Model* model1 = dynamic_cast<Krayo::Scene::Model*>(modelResult.first);
    if (modelResult.second)
    {
        model1->Init(modelDesc);
        model1->SetPosition(-2.0f, 1.0f, 0.0f);
    }

    modelDesc.materials.clear();
    modelDesc.materials.push_back(boxMatNoTex);

    // untextured cube
    modelResult = scene.GetComponent(Krayo::Scene::ComponentType::Model, "box2");
    Krayo::Scene::Model* model2 = dynamic_cast<Krayo::Scene::Model*>(modelResult.first);
    if (modelResult.second)
    {
        model2->Init(modelDesc);
        model2->SetPosition(2.0f, 1.0f, 0.0f);
    }

    Krayo::Scene::Object* obj = scene.CreateObject();
    obj->SetComponent(model1);

    obj = scene.CreateObject();
    obj->SetComponent(model2);

    auto lightResult = scene.GetComponent(Krayo::Scene::ComponentType::Light, "light");
    gLight = dynamic_cast<Krayo::Scene::Light*>(lightResult.first);
    gLight->SetDiffuseIntensity(1.0f, 1.0f, 1.0f);
    gLight->SetPosition(3.0f, 5.0f, 0.0f);

    Krayo::Scene::Object* lightObj = scene.CreateObject();
    lightObj->SetComponent(gLight);

    //std::random_device randomDevice;
    std::mt19937 randomGen(0);

    gLights.resize(LIGHT_COUNT);
    for (uint32_t i = 0; i < LIGHT_COUNT; ++i)
    {
        auto lres = scene.GetComponent(Krayo::Scene::ComponentType::Light, "light" + std::to_string(i));
        gLights[i] = dynamic_cast<Krayo::Scene::Light*>(lres.first);

        float colorX = static_cast<float>(randomGen()) / static_cast<float>(randomGen.max());
        float colorY = static_cast<float>(randomGen()) / static_cast<float>(randomGen.max());
        float colorZ = static_cast<float>(randomGen()) / static_cast<float>(randomGen.max());
        gLights[i]->SetDiffuseIntensity(colorX, colorY, colorZ);
        gLights[i]->SetPosition(colorX * LIGHT_AREA_X - (LIGHT_AREA_X / 2.0f),
                                colorY * LIGHT_AREA_Y - (LIGHT_AREA_Y / 2.0f) + 0.5f,
                                colorZ * LIGHT_AREA_Z - (LIGHT_AREA_Z / 2.0f));
        gLights[i]->SetRange(1.5f);

        Krayo::Scene::Object* o = scene.CreateObject();
        o->SetComponent(gLights[i]);
    }

    for (int i = -EMITTERS_LIMIT; i < EMITTERS_LIMIT + 1; ++i)
    {
        auto emitterResult = scene.GetComponent(Krayo::Scene::ComponentType::Emitter, "emitter" + std::to_string(i + EMITTERS_LIMIT));
        gEmitters[i + EMITTERS_LIMIT] = dynamic_cast<Krayo::Scene::Emitter*>(emitterResult.first);

        gEmitters[i + EMITTERS_LIMIT]->SetParticleLimit(EMITTERS_PARTICLE_LIMIT);
        gEmitters[i + EMITTERS_LIMIT]->SetSpawnPeriod(4.0f / static_cast<float>(EMITTERS_PARTICLE_LIMIT));
        gEmitters[i + EMITTERS_LIMIT]->SetLifeTime(4.0f);
        gEmitters[i + EMITTERS_LIMIT]->SetPosition(lkCommon::Math::Vector4(i * 6.0f, 10.0f, -0.25f, 1.0f));

        Krayo::Scene::Object* o = scene.CreateObject();
        o->SetComponent(gEmitters[i + EMITTERS_LIMIT]);
    }
*/
