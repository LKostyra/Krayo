#include "Krayo/Engine.hpp"
#include "API/EngineImpl.hpp"


namespace Krayo {

Engine::Engine()
    : mImpl(std::make_unique<Impl>())
{
}

Engine::~Engine()
{
}

bool Engine::Init(const EngineDesc& desc)
{
    return mImpl->Init(desc);
}

void Engine::MainLoop()
{
    return mImpl->MainLoop();
}

Krayo::Scene::Map Engine::CreateMap(const std::string& name)
{
    return Krayo::Scene::Map(mImpl->CreateMap(name));
}

Krayo::Scene::Map Engine::GetMap(const std::string& name)
{
    return Krayo::Scene::Map(mImpl->GetMap(name));
}

void Engine::SetCurrentMap(const Krayo::Scene::Map& map)
{
    return mImpl->SetCurrentMap(map.mImpl);
}

Krayo::Resource::Manager& Engine::GetResourceManager()
{
    return mImpl->GetResourceManager();
}

bool Engine::RegisterToEvent(const Events::ID id, Events::ISubscriber* subscriber)
{
    return mImpl->RegisterToEvent(id, subscriber);
}

void Engine::EmitEvent(const Events::ID id, const Events::IMessage* message)
{
    mImpl->EmitEvent(id, message);
}

} // namespace Krayo
