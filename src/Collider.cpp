#include "Collider.h"

Collider::~Collider()
{
    Physics::Instance().RemoveRigidBody(m_RigidBody);

    delete m_RigidBody->getMotionState();
    delete m_RigidBody;
    delete m_Shape;
}