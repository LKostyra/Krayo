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

void Engine::Draw(const float frameTime) const
{
    return mImpl->Draw(frameTime);
}

} // namespace Krayo
