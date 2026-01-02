#include "Transform.h"

void Transform::SetPosition(const glm::vec3& position)
{
    m_Position = position;
    calculate();
}

void Transform::SetRotation(const glm::vec3& euler)
{
    m_Rotation = glm::quat(glm::radians(euler));
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
    if (m_Parent)
    {
        auto& parentChildren = m_Parent->m_Children;
        parentChildren.erase(std::remove(parentChildren.begin(), parentChildren.end(), this), parentChildren.end());
    }

    m_Parent = parent;
    if (m_Parent)
        m_Parent->m_Children.push_back(this);

    calclateParent(m_Parent ? m_Parent->GetWorldMatrix() : glm::mat4(1.0f));
}

void Transform::calculate()
{
    glm::mat4 Trl = glm::translate(glm::mat4(1.0f), m_Position);
    glm::mat4 Rot = glm::mat4_cast(m_Rotation);
    glm::mat4 Scl = glm::scale(glm::mat4(1.0f), m_Scale);

    m_LocalMatrix = Trl * Rot * Scl;

    calclateParent(m_Parent ? m_Parent->GetWorldMatrix() : glm::mat4(1.0f));
}

void Transform::calclateParent(glm::mat4 parent)
{
    m_WorldMatrix = parent * m_LocalMatrix;

    m_ForwardDir = glm::normalize(-glm::vec3(m_WorldMatrix[2]));
    m_RightDir = glm::normalize(glm::vec3(m_WorldMatrix[0]));
    m_UpDir = glm::normalize(glm::vec3(m_WorldMatrix[1]));

    for (auto child : m_Children)
        child->calclateParent(m_WorldMatrix);
}
