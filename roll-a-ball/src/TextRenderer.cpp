#include "TextRenderer.h"

#include "Text.h"
#include "Font.h"
#include "ShaderManager.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

TextRenderer::TextRenderer()
    :m_Shader(ShaderManager::Instance().GetShader(RENDERER_SHADER_TEXT))
{
    // Creates VAO & VBO
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * 6, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);

    // layout(location = 0): vec4(x, y, u, v)
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Create Texture
    glGenTextures(1, &m_TextureID);

    // Create FBO
    glGenFramebuffers(1, &m_FBO);
}

TextRenderer::~TextRenderer()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteTextures(1, &m_TextureID);
    glDeleteFramebuffers(1, &m_FBO);
}

void TextRenderer::Render(const std::u32string& text, FontPtr font) const
{
    float x = 0.0f;
    float y = 0.0f;

    float maxTop = 0.0f;
    float maxBottom = 0.0f;

    std::vector<unsigned int> textures(text.size());
    std::vector<std::array<glm::vec4, 6>> vertices(text.size());

    for (char32_t c : text) 
    {
        Glyph glyph = font->GetGlyph(c);
        maxTop    = std::max(maxTop, (float)glyph.Bearing.y);
        maxBottom = std::max(maxBottom, (float)(glyph.Size.y - glyph.Bearing.y));
    }

    for (size_t i = 0; i < text.size(); ++i)
    {
        Glyph glyph = font->GetGlyph(text[i]);
        textures[i] = glyph.TextureID;

        float xpos = x + glyph.Bearing.x;
        float ypos = y + (maxTop - glyph.Bearing.y);

        float w = glyph.Size.x;
        float h = glyph.Size.y;

        // Calculate quad vertices
        vertices[i][0] = glm::vec4(xpos,     ypos + h, 0.0f, 1.0f);
        vertices[i][1] = glm::vec4(xpos,     ypos,     0.0f, 0.0f);
        vertices[i][2] = glm::vec4(xpos + w, ypos,     1.0f, 0.0f);
        vertices[i][3] = glm::vec4(xpos,     ypos + h, 0.0f, 1.0f);
        vertices[i][4] = glm::vec4(xpos + w, ypos,     1.0f, 0.0f);
        vertices[i][5] = glm::vec4(xpos + w, ypos + h, 1.0f, 1.0f);

        maxTop    = std::max(maxTop,    (float)glyph.Bearing.y);
        maxBottom = std::max(maxBottom, (float)(glyph.Size.y - glyph.Bearing.y));

        x += (glyph.Advance >> 6);
    }

    int textWidth  = static_cast<int>(x);
    int textHeight = static_cast<int>(maxTop + maxBottom);

    // Rendering text image
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textWidth, 50, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(textWidth), 0.0f, static_cast<float>(textHeight));
    glViewport(0, 0, textWidth, textHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    m_Shader->Bind();
    m_Shader->Set("u_Albedo", glm::vec4(1.0f));
    m_Shader->Set("u_Projection", projection);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    for(size_t i = 0; i < vertices.size(); ++i)
    {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * 6, vertices[i].data());
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    m_Shader->Unbind();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}