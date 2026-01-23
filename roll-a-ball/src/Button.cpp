#include "Button.h"

Button::Button(const std::shared_ptr<Entity> entity)
    :Component(entity)
{
}

Button::~Button()
{
}

glm::vec4 Button::GetColor() const
{
    return m_Color;
}

void Button::SetStateNormal()
{
    m_Color = m_NormalColor;
}

void Button::SetStateHover()
{
    m_Color = m_HighlightedColor;
}

void Button::SetStatePressed()
{
    m_Color = m_PressedColor;
    for (auto& cb : m_OnClickedCallbacks)
        cb();
}

void Button::SetStateDisabled()
{
    m_Color = m_DisabledColor;
}

void Button::SetNormalColor(const glm::vec4& color)
{
    m_NormalColor = color;
}

void Button::SetHighlightedColor(const glm::vec4& color)
{
    m_HighlightedColor = color;
}

void Button::SetPressedColor(const glm::vec4& color)
{
    m_PressedColor = color;
}

void Button::SetSelectedColor(const glm::vec4& color)
{
    m_SelectedColor = color;
}

void Button::SetDisabledColor(const glm::vec4& color)
{
    m_DisabledColor = color;
}

void Button::AddOnClick(Callback cb)
{
    m_OnClickedCallbacks.push_back(cb);
}
