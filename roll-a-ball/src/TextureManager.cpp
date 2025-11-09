#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "TextureManager.h"
#include "Texture.h"

TextureManager& TextureManager::Instance()
{
	static TextureManager instance;
	return instance;
}

void TextureManager::LoadTexture(const std::string& textureName)
{
    TexturePtr texture = std::make_shared<Texture>();
    glGenTextures(1, &texture->m_ID);
    glBindTexture(GL_TEXTURE_2D, texture->m_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data = stbi_load(
        textureName.c_str(), &texture->m_Width, &texture->m_Height, &texture->m_Channels, 0);
    if (data)
    {
        auto channel = GL_RGB;
        switch (texture->m_Channels)
        {
        case 1: channel = GL_RED; break;
        case 4: channel = GL_RGBA; break;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, channel, texture->m_Width, texture->m_Height, 0, channel, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    m_Textures[textureName] = texture;
}

TexturePtr TextureManager::GetTexture(const std::string& textureName)
{
	return m_Textures[textureName];
}

void TextureManager::Clear()
{
	m_Textures.clear();
}
