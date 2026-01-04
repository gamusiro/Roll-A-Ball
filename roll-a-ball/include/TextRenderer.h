#ifndef ROLL_A_BALL_INCLUDE_TEXT_RENDERER_H_
#define ROLL_A_BALL_INCLUDE_TEXT_RENDERER_H_
#include "Config.h"

class TextRenderer
{
public:
    TextRenderer();
    ~TextRenderer();

public:
    void Render(const std::u32string& text, FontPtr font) const;

public:
    uint32_t GetTextureID() const { return m_TextureID; }

private:
    uint32_t m_VAO;
    uint32_t m_VBO;
    uint32_t m_FBO;
    uint32_t m_TextureID;
    ShaderPtr m_Shader;
};

#endif //!ROLL_A_BALL_INCLUDE_TEXT_RENDERER_H_