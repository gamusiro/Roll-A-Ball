#include "Material.h"

Material::Material(const std::shared_ptr<Entity> entity)
    : Component(entity),
    m_Albedo(glm::vec4(1.0f)),
    m_Shader(ShaderManager::Instance().GetShader(SHADER_DEFAULT_3D))
{
}

Material::~Material()
{
}

void Material::SetAlbedo(const glm::vec4& albedo)
{
    m_Albedo = albedo;
}

void Material::SetShader(const ShaderPtr shader)
{
    m_Shader = shader;
}