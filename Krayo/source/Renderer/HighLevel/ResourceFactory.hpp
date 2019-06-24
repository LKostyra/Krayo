#pragma once

#include "Prerequisites.hpp"
#include "Renderer/LowLevel/Device.hpp"
#include "Renderer/LowLevel/Buffer.hpp"
#include "Renderer/LowLevel/Texture.hpp"

#include <list>


namespace Krayo {
namespace Renderer {

class ResourceFactory final
{
    DevicePtr mDevice;

    ResourceFactory();
    ResourceFactory(const ResourceFactory&) = delete;
    ResourceFactory(ResourceFactory&&) = delete;
    ResourceFactory& operator=(const ResourceFactory&) = delete;
    ResourceFactory& operator=(ResourceFactory&&) = delete;
    ~ResourceFactory();

public:
    static ResourceFactory& Instance();

    bool Init(const DevicePtr& device);
    void Release();

    BufferPtr CreateBuffer(const BufferDesc& desc);
    TexturePtr CreateTexture(const TextureDesc& desc);
};

} // namespace Renderer
} // namespace Krayo
