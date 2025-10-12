#ifndef ROLL_A_BALL_INCLUDE_TEXT_H_
#define ROLL_A_BALL_INCLUDE_TEXT_H_
#include "Config.h"

#include "Component.h"

class Text : public Component
{
public:
    Text(const std::shared_ptr<Entity> entity, const std::u32string& text, FontPtr font);
    ~Text();

public:
    void SetText(const std::u32string& text) { m_Text = text; }
    const std::u32string& GetText() const { return m_Text; }

private:
    std::u32string m_Text;
    const FontPtr m_Font;

    unsigned int m_VAO;
    unsigned int m_VBOPos;
    unsigned int m_VBOTex;

private:
    friend class TextRenderer;
};

#endif //!ROLL_A_BALL_INCLUDE_TEXT_H_