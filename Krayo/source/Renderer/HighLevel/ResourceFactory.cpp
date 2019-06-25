#include "Renderer/HighLevel/ResourceFactory.hpp"


namespace Krayo {
namespace Renderer {

ResourceFactory::ResourceFactory()
{
}

ResourceFactory::~ResourceFactory()
{
    Release();
}

ResourceFactory& ResourceFactory::Instance()
{
    static ResourceFactory instance;
    return instance;
}

bool ResourceFactory::Init(const DevicePtr& device)
{
    mDevice = device;
    return true;
}

void ResourceFactory::Release()
{
    mDevice.reset();
}

BufferPtr ResourceFactory::CreateBuffer(const BufferDesc& desc)
{
    BufferPtr b = std::make_shared<Buffer>();
    if (!b->Init(mDevice, desc))
        return nullptr;

    return std::move(b);
}

TexturePtr ResourceFactory::CreateTexture(const TextureDesc& desc)
{
    TexturePtr t = std::make_shared<Texture>();
    if (!t->Init(mDevice, desc))
        return nullptr;

    return std::move(t);
}

} // namespace Renderer
} // namespace Krayo
