#ifndef ROLL_A_BALL_INCLUDE_TEXT_H_
#define ROLL_A_BALL_INCLUDE_TEXT_H_
#include "Config.h"

#include "Component.h"
#include "TextRenderer.h"

class Text : public Component
{
public:
    Text(const std::shared_ptr<Entity> entity, const std::u32string& text, FontPtr font);
    ~Text();

public:
    void SetText(const std::u32string& text);
    const std::u32string& GetText() const { return m_Text; }

private:
    std::u32string m_Text;
    const FontPtr m_Font;
    TextRenderer m_Renderer;

private:
    friend class CanvasRenderer;
};

#endif //!ROLL_A_BALL_INCLUDE_TEXT_H_