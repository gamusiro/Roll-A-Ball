#ifndef ROLL_A_BALL_INCLUDE_FONT_H_
#define ROLL_A_BALL_INCLUDE_FONT_H_
#include "Config.h"

struct Glyph
{
    unsigned int TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
};

class Font
{
public:
    ~Font();
    const Glyph& GetGlyph(char32_t c) const;
    void MakeGlyphs(const std::u32string& str);
    
private:
    FT_Face m_Face;
    std::map<char32_t, Glyph> m_Glyphs;

private:
    friend class FontManager;
};

#endif //!ROLL_A_BALL_INCLUDE_FONT_H_