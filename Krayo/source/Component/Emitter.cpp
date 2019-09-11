#include "Emitter.hpp"


namespace Krayo {
namespace Component {
namespace Internal {

Emitter::Emitter(const std::string& name)
    : IComponent(name)
    , mData()
{
}

void Emitter::Init(const EmitterDesc& desc)
{
    mData.pos = desc.pos;
    mData.particleLimit = desc.particleLimit;
    mData.spawnPeriod = desc.spawnPeriod;
    mData.spawnTimer = 0.0f;
    mData.particleDataOffset = 0;
}

} // namespace Internal
} // namespace Component
} // namespace Krayo
