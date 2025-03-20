#include "Transform.h"

void Transform::SetPosition(const glm::vec3& position) 
{ 
    m_Position = position;
    calculate();
}

void Transform::SetRotation(const glm::vec3& euler) 
{ 
    m_Rotation = glm::yawPitchRoll(euler.y, euler.x, euler.z);
    calculate();
}

void Transform::SetRotation(const glm::quat& quat) 
{ 
    m_Rotation = quat;
    calculate();
}

void Transform::SetScale (const glm::vec3& scale) 
{ 
    m_Scale = scale;
    calculate();
}

void Transform::calculate()
{
    glm::mat4 Trl = glm::translate(glm::mat4(1.0f), m_Position);
    glm::mat4 Rot = glm::mat4_cast(m_Rotation);
    glm::mat4 Scl = glm::scale(glm::mat4(1.0f), m_Scale);

    m_LocalMatrix = Trl * Rot * Scl;
    m_WorldMatrix = this->calclateParent();

    m_ForwardDir = glm::rotate(m_Rotation, glm::vec3(0.0f, 0.0f, -1.0f));
    m_RightDir = glm::normalize(glm::cross(m_ForwardDir, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_UpDir = glm::normalize(glm::cross(m_RightDir, m_ForwardDir));
}

const glm::mat4 Transform::calclateParent() const
{
    if (m_Parent)
        return m_LocalMatrix * m_Parent->calclateParent();

    return glm::mat4(1.0f);
}