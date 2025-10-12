#include "TextRenderer.h"

#include "Text.h"
#include "Font.h"

void TextRenderer::Render(const Text& text) const
{
    float x = 0.0f;
    float y = 0.0f;
    float scale = 1.0f;

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(text.m_VAO);

    for (char32_t c : text.m_Text) 
    {
        Glyph glyph = text.m_Font->GetGlyph(c);

        float xpos = x + glyph.Bearing.x * scale;
        float ypos = y - (glyph.Size.y - glyph.Bearing.y) * scale;

        float w = glyph.Size.x * scale;
        float h = glyph.Size.y * scale;

        glm::vec3 positions[6] = {
            { xpos,        ypos + h,  0.0f },
            { xpos,        ypos,      0.0f },
            { xpos + w,    ypos,      0.0f },

            { xpos,        ypos + h,  0.0f },
            { xpos + w,    ypos,      0.0f },
            { xpos + w,    ypos + h,  0.0f }
        };

        glm::vec2 texcoords[6] = {
            { 0.0f, 0.0f },
            { 0.0f, 1.0f },
            { 1.0f, 1.0f },

            { 0.0f, 0.0f },
            { 1.0f, 1.0f },
            { 1.0f, 0.0f }
        };


        glBindTexture(GL_TEXTURE_2D, glyph.TextureID);

        glBindBuffer(GL_ARRAY_BUFFER, text.m_VBOPos);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);

        glBindBuffer(GL_ARRAY_BUFFER, text.m_VBOTex);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(texcoords), texcoords);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (glyph.Advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}