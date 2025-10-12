#include "Font.h"

#include "Logger.h"

Font::~Font()
{
    for(auto glyph : m_Glyphs)
        glDeleteTextures(1, &glyph.second.TextureID);

    m_Glyphs.clear();
    FT_Done_Face(m_Face);
}

const Glyph& Font::GetGlyph(char32_t c) const 
{
    return m_Glyphs.at(c);
}

void Font::MakeGlyphs(const std::u32string& str)
{
    FT_Set_Pixel_Sizes(m_Face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(char32_t c : str)
    {
        if(FT_Load_Char(m_Face, c, FT_LOAD_RENDER))
        {
            LOG_CORE_ERROR("Failed to load character");
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            m_Face->glyph->bitmap.width,
            m_Face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            m_Face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        Glyph glyph = {
            texture,
            glm::ivec2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
            glm::ivec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
            static_cast<unsigned int>(m_Face->glyph->advance.x)
        };
        m_Glyphs.insert({c, glyph});
    }
}