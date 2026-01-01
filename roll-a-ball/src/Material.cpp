#include "Material.h"

#include "TextureManager.h"

Material::Material(const std::shared_ptr<Entity> entity)
    : Component(entity),
    m_Albedo(glm::vec4(1.0f)),
    m_Shader(ShaderManager::Instance().GetShader(RENDERER_SHADER_DEFAULT)),
    m_AlbedoTexture(TextureManager::Instance().GetTexture(TEXTURE_WHITE)),
    m_NormalTexture(TextureManager::Instance().GetTexture(TEXTURE_WHITE)),
    m_MetalnessTexture(TextureManager::Instance().GetTexture(TEXTURE_WHITE)),
    m_RoughnessTexture(TextureManager::Instance().GetTexture(TEXTURE_WHITE)),
    m_DisplacementTexture(TextureManager::Instance().GetTexture(TEXTURE_WHITE))
{
}

Material::~Material()
{
}

void Material::SetAlbedo(const glm::vec4& albedo)
{
    m_Albedo = albedo;
}

void Material::SetAlbedoTexture(const TexturePtr& texture)
{
    m_AlbedoTexture = texture;
}

void Material::SetNormalTexture(const TexturePtr& texture)
{
    m_NormalTexture = texture;
}

void Material::SetMetalnessTexture(const TexturePtr& texture)
{
    m_MetalnessTexture = texture;
}

void Material::SetRoughnessTexture(const TexturePtr& texture)
{
    m_RoughnessTexture = texture;
}

void Material::SetDisplacementTexture(const TexturePtr& texture)
{
    m_DisplacementTexture = texture;
}

void Material::SetShader(const ShaderPtr shader)
{
    m_Shader = shader;
}