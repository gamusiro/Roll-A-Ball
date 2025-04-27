#include "Collider.h"

Collider::Collider(const Entity* entity)
    : Component(entity)
{   
}

Collider::~Collider()
{
    Physics::Instance().RemoveRigidBody(m_RigidBody);

    delete m_RigidBody->getMotionState();
    delete m_RigidBody;
    delete m_Shape;
}