#ifndef ROLL_A_BALL_INCLUDE_BUTTON_H_
#define ROLL_A_BALL_INCLUDE_BUTTON_H_
#include "Config.h"

#include "Component.h"

class Button : public Component
{
public:
    using Callback = std::function<void()>;

public:
    Button(const std::shared_ptr<Entity> entity);
    ~Button();

public:
    glm::vec4 GetColor() const;

public:
    void SetStateNormal();
    void SetStateHover();
    void SetStatePressed();
    void SetStateDisabled();

public:
    void SetNormalColor(const glm::vec4& color);
    void SetHighlightedColor(const glm::vec4& color);
    void SetPressedColor(const glm::vec4& color);
    void SetSelectedColor(const glm::vec4& color);
    void SetDisabledColor(const glm::vec4& color);

public:
    void AddOnClick(Callback cb);

private:
    glm::vec4 m_NormalColor = glm::vec4(1.0f);
    glm::vec4 m_HighlightedColor = glm::vec4(0.9607f, 0.9607f, 0.9607f, 1.0f);
    glm::vec4 m_PressedColor = glm::vec4(0.7843f, 0.7843f, 0.7843f, 1.0f);
    glm::vec4 m_SelectedColor = glm::vec4(0.9607f, 0.9607f, 0.9607f, 1.0f);
    glm::vec4 m_DisabledColor = glm::vec4(0.7843f, 0.7843f, 0.7843f, 0.5f);

    glm::vec4 m_Color = glm::vec4(1.0f);

    std::vector<Callback> m_OnClickedCallbacks;
};

#endif //!ROLL_A_BALL_INCLUDE_BUTTON_H_