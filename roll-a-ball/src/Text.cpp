#include "Text.h"

Text::Text(const std::shared_ptr<Entity> entity, const std::u32string& text, FontPtr font)
        :Component(entity), m_Font(font) 
{
    SetText(text);
}

Text::~Text()
{
}

void Text::SetText(const std::u32string& text)
{
    m_Text = text;
    m_Renderer.Render(m_Text, m_Font, m_Color);
}

void Text::SetColor(const glm::vec4& color)
{
    m_Color = color;
    m_Renderer.Render(m_Text, m_Font, m_Color);
}