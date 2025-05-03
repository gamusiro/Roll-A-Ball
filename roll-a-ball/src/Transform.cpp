#include "Transform.h"

void Transform::SetPosition(const glm::vec3& position) 
{
    m_Position = position;
    calculate();
}

void Transform::SetRotation(const glm::vec3& euler) 
{
    m_Rotation = glm::yawPitchRoll(glm::radians(euler.y), glm::radians(euler.x), glm::radians(euler.z));
    calculate();
}

void Transform::SetRotation(const glm::quat& quat) 
{
    m_Rotation = glm::normalize(quat);
    calculate();
}

void Transform::SetScale(const glm::vec3& scale) 
{
    m_Scale = scale;
    calculate();
}

void Transform::SetParent(Transform* parent)
{
    m_Parent = parent;
    parent->m_Children.push_back(this);
}

void Transform::calculate()
{
    glm::mat4 Trl = glm::translate(glm::mat4(1.0f), m_Position);
    glm::mat4 Rot = glm::mat4_cast(m_Rotation);
    glm::mat4 Scl = glm::scale(glm::mat4(1.0f), m_Scale);

    m_LocalMatrix = Trl * Rot * Scl;
    this->calclateParent(glm::mat4(1.0f));
}

void Transform::calclateParent(glm::mat4 parent)
{
    m_WorldMatrix = parent * m_LocalMatrix;
    for (auto child : m_Children)
        child->calclateParent(m_WorldMatrix);

    m_Position = m_WorldMatrix[3];

    m_ForwardDir = -glm::vec3(m_WorldMatrix[2]);
    m_RightDir = glm::vec3(m_WorldMatrix[0]);
    m_UpDir = glm::vec3(m_WorldMatrix[1]);
}