#include "Krayo/Engine.hpp"
#include "API/EngineImpl.hpp"


namespace Krayo {

Engine::Engine()
    : mImpl(new Engine::Impl())
{
}

Engine::~Engine()
{
    delete mImpl;
    mImpl = nullptr;
}

bool Engine::Init(const EngineDesc& desc)
{
    return mImpl->Init(desc);
}

void Engine::MainLoop()
{
    return mImpl->MainLoop();
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
