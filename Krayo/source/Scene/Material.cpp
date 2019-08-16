#include "Scene/Material.hpp"

#include <lkCommon/Utils/Logger.hpp>
#include <lkCommon/Utils/Image.hpp>


namespace Krayo {
namespace Scene {

Material::Material(const std::string& name)
    : mMaterialName(name)
    , mColor(1.0f)
    , mDiffuseTexture(nullptr)
    , mNormalTexture(nullptr)
    , mMaskTexture(nullptr)
{
}

Material::~Material()
{
}

bool Material::CreateRendererTexture(const std::string& imagePath, VkImageUsageFlags usage, Renderer::TexturePtr& texture)
{
    lkCommon::Utils::Image<lkCommon::Utils::PixelUint4> image;
    if (!image.Load(imagePath))
        return false;

    image.GenerateMipmaps(lkCommon::Utils::Sampling::BILINEAR);

    std::vector<Renderer::TextureDataDesc> textures;
    textures.reserve(image.GetMipmaps().size() + 1);
    textures.emplace_back(image.GetPixels().data(), image.GetPixels().size() * sizeof(lkCommon::Utils::PixelUint4));
    for (uint32_t i = 0; i < image.GetMipmaps().size(); ++i)
        textures.emplace_back(image.GetMipmaps()[i].data(), image.GetMipmaps()[i].size() * sizeof(lkCommon::Utils::PixelUint4));

    Renderer::TextureDesc texDesc;
    texDesc.width = image.GetWidth();
    texDesc.height = image.GetHeight();
    texDesc.usage = usage;
    texDesc.data = textures.data();
    texDesc.mipmapCount = static_cast<uint32_t>(textures.size());
    texDesc.layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    texDesc.format = VK_FORMAT_B8G8R8A8_UNORM;

    texture = Renderer::ResourceFactory::Instance().CreateTexture(texDesc);
    return (texture != nullptr);
}

} // namespace Scene
} // namespace Krayo
