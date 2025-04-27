#include "Collider.h"

#include "CollisionCallback.h"

Collider::Collider(const Entity* entity)
    : Component(entity)
{
    m_Callback = new CollisionCallback();
}

Collider::~Collider()
{
    Physics::Instance().RemoveRigidBody(m_RigidBody);

    delete m_Callback;
    delete m_RigidBody->getMotionState();
    delete m_RigidBody;
    delete m_Shape;
}