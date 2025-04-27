#ifndef ROLL_A_BALL_INCLUDE_MATERIAL_H_
#define ROLL_A_BALL_INCLUDE_MATERIAL_H_
#include "Config.h"

#include "Component.h"
#include "ShaderManager.h"


class Material : public Component
{
public:
    Material(const Entity* entity);
    ~Material();

public:
    void SetAlbedo(const glm::vec4& albedo);
    void SetShader(const ShaderPtr shader);

public:
    inline const glm::vec4 GetAlbedo() const { return m_Albedo; }
    inline const ShaderPtr GetShader() const { return m_Shader; }

private:
    glm::vec4 m_Albedo;
    ShaderPtr m_Shader;
};

#endif //!ROLL_A_BALL_INCLUDE_MATERIAL_H_