#ifndef ROLL_A_BALL_INCLUDE_RECT_TRANSFORM_H_
#define ROLL_A_BALL_INCLUDE_RECT_TRANSFORM_H_
#include "Config.h"

#include "Component.h"

class RectTransform : public Component
{
public:
    RectTransform(const std::shared_ptr<Entity> entity);
    ~RectTransform();

public:
    void SetPosition(const glm::vec2& position);
    void SetSize(const glm::vec2& size);
    void SetParent(RectTransform* parent);
    void SetRotation(const glm::vec3& euler);
    void SetScale(const glm::vec3& scale);

    inline const glm::vec2 GetPosition() const { return m_Position; }
    inline const glm::mat4 GetLocalMatrix() const { return m_LocalMatrix; }
	inline const glm::mat4 GetWorldMatrix() const { return m_WorldMatrix; }
    inline const glm::vec2 GetSize() const { return m_Size; }

private:
	void calculate();
	void calclateParent(const glm::mat4& parent);

private:
    RectTransform* m_Parent;
    glm::vec2 m_Position;
    glm::vec2 m_Size;
    glm::quat m_Rotation;
    glm::vec3 m_Scale;


    glm::mat4 m_LocalMatrix = glm::mat4(1.0f);
	glm::mat4 m_WorldMatrix = glm::mat4(1.0f);
    std::vector<RectTransform*> m_Children;
};


#endif //! ROLL_A_BALL_INCLUDE_RECT_TRANSFORM_H_