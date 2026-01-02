#include "RectTransform.h"


RectTransform::RectTransform(const std::shared_ptr<Entity> entity)
    :Component(entity),
    m_Parent(nullptr)
{
}

RectTransform::~RectTransform()
{
}

void RectTransform::SetPosition(const glm::vec2& position)
{
    m_Position = position;
    calculate();
}

void RectTransform::SetSize(const glm::vec2& size)
{
    m_Size = size;
    calculate();
}

void RectTransform::SetParent(RectTransform* parent)
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

void RectTransform::calculate()
{
    glm::mat4 Trl = glm::translate(glm::mat4(1.0), glm::vec3(m_Position, 0.0f));
    glm::mat4 Rot = glm::mat4(1.0f);
    glm::mat4 Scl = glm::mat4(1.0f);

    m_LocalMatrix = Trl * Rot * Scl;
    calclateParent(m_Parent ? m_Parent->GetWorldMatrix() : glm::mat4(1.0f));
}

void RectTransform::calclateParent(const glm::mat4& parent)
{
    m_WorldMatrix = parent * m_LocalMatrix;

    for (auto* child : m_Children)
        child->calclateParent(m_WorldMatrix);
}