#include "RigidBody.h"

RigidBody::RigidBody(const Collider& collider)
    :m_RigidBody(collider.m_RigidBody)
{
}

void RigidBody::AddImpulse(const glm::vec3& impulse)
{
    m_RigidBody->applyCentralImpulse(VEC3_GLM_2_BT(impulse));
}