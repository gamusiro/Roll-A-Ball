#ifndef ROLL_A_BALL_INCLUDE_MATERIAL_H_
#define ROLL_A_BALL_INCLUDE_MATERIAL_H_
#include "Config.h"

#include "Component.h"
#include "ShaderManager.h"


class Material : public Component
{
public:
    Material(const std::shared_ptr<Entity> entity);
    ~Material();

public:
    void SetAlbedo(const glm::vec4& albedo);
    void SetAlbedoTexture(const TexturePtr& texture);
    void SetNormalTexture(const TexturePtr& texture);
    void SetMetalnessTexture(const TexturePtr& texture);
    void SetRoughnessTexture(const TexturePtr& texture);
    void SetDisplacementTexture(const TexturePtr& texture);
    void SetShader(const ShaderPtr shader);

public:
    inline const glm::vec4 GetAlbedo() const { return m_Albedo; }
    inline const TexturePtr GetAlbedoTexture() const { return m_AlbedoTexture; }
    inline const TexturePtr GetNormalTexture() const { return m_NormalTexture; }
    inline const TexturePtr GetMetalnessTexture() const { return m_MetalnessTexture; }
    inline const TexturePtr GetRoughnessTexture() const { return m_RoughnessTexture; }
    inline const TexturePtr GetDisplacementTexture() const { return m_DisplacementTexture; }
    inline const ShaderPtr GetShader() const { return m_Shader; }

private:
    glm::vec4 m_Albedo;

    TexturePtr m_AlbedoTexture;
    TexturePtr m_NormalTexture;
    TexturePtr m_MetalnessTexture;
    TexturePtr m_RoughnessTexture;
    TexturePtr m_DisplacementTexture;

    ShaderPtr m_Shader;
};

#endif //!ROLL_A_BALL_INCLUDE_MATERIAL_H_