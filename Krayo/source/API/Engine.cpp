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

bool Engine::RegisterToEvent(EventID id, IEventSubscriber* subscriber)
{
    return mImpl->RegisterToEvent(id, subscriber);
}

void Engine::EmitEvent(IEventMessage* message)
{
    mImpl->EmitEvent(message);
}

} // namespace Krayo
