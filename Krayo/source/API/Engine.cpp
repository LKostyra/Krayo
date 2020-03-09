#include "Krayo/Engine.hpp"

#include "Engine.hpp"

#include "Krayo/Map.hpp"


namespace Krayo {

Engine::Engine()
    : mImpl(std::make_unique<Internal::Engine>())
{
}

// this destructor has to be here so std::unique_ptr knows how Engine::Impl
// is defined and compiles properly
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

Krayo::Resource::Manager& Engine::GetResourceManager()
{
    return mImpl->GetResourceManager();
}

Krayo::Map Engine::CreateMap(const std::string& name)
{
    return Krayo::Map(mImpl->CreateMap(name));
}

void Engine::SetCurrentMap(Krayo::Map& map)
{
    mImpl->SetCurrentMap(map.mImpl);
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
