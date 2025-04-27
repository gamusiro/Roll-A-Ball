#include "Collider.h"

Collider::Collider(const Entity* entity)
    : Component(entity),
    m_Shape(nullptr), m_RigidBody(nullptr)
{
}

Collider::~Collider()
{
    Physics::Instance().RemoveRigidBody(m_RigidBody);

    delete m_RigidBody->getMotionState();
    delete m_RigidBody;
    delete m_Shape;
}

void Collider::SetTrigger(bool isTrigger)
{
    int flags = m_RigidBody->getCollisionFlags();
    if(!isTrigger)
        flags &= ~btCollisionObject::CF_NO_CONTACT_RESPONSE;
    else
        flags |= btCollisionObject::CF_NO_CONTACT_RESPONSE;
    m_RigidBody->setCollisionFlags(flags);
}

bool Collider::IsTrigger() const
{
    return m_RigidBody->getFlags() & btCollisionObject::CF_NO_CONTACT_RESPONSE;
}