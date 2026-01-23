#include "Image.h"

#include "TextureManager.h"

Image::Image(const std::shared_ptr<Entity> entity)
    :Component(entity),
    m_SourceImage(TextureManager::Instance().GetTexture(TEXTURE_WHITE))
{
}

Image::~Image()
{
}

void Image::SetSourceImage(const std::string& textureName)
{
    TextureManager& tm = TextureManager::Instance();
    m_SourceImage = tm.GetTexture(textureName);
    if(!m_SourceImage)
        m_SourceImage = tm.GetTexture(TEXTURE_WHITE);
}

void Image::SetColor(const glm::vec4& color)
{
    m_Color = color;
}