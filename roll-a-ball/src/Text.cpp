#include "Text.h"

Text::Text(const std::shared_ptr<Entity> entity, const std::u32string& text, FontPtr font)
        :Component(entity), m_Text(text), m_Font(font) 
{
}

Text::~Text()
{
}

void Text::SetText(const std::u32string& text)
{
    m_Text = text;
    m_Renderer.Render(m_Text, m_Font);
}