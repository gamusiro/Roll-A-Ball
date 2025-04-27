#include "RigidBody.h"

RigidBody::RigidBody(const Entity* entity, const Collider& collider)
    : Component(entity),
    m_RigidBody(collider.m_RigidBody)
{
    m_RigidBody->setActivationState(DISABLE_DEACTIVATION);
}

void RigidBody::AddImpulse(const glm::vec3& impulse)
{
    m_RigidBody->applyCentralImpulse(VEC3_GLM_2_BT(impulse));
}