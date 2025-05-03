#include "SphereCollider.h"

SphereCollider::SphereCollider(const std::shared_ptr<Entity> entity, float radius, const ColliderParameter& parameter)
    : Collider(entity)
{
    m_Shape = new btSphereShape(radius);

    btVector3 localInetia(0.0f, 0.0f, 0.0f);
    if (parameter.mass != 0.0f) {
        m_Shape->calculateLocalInertia(parameter.mass, localInetia);
    }

    btDefaultMotionState* motion = new btDefaultMotionState(parameter.transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(parameter.mass, motion, m_Shape, localInetia);
    m_RigidBody = new btRigidBody(rbInfo);
    m_RigidBody->setFriction(parameter.friction);
    m_RigidBody->setUserPointer(&m_Handle);
    SetTrigger(parameter.isTrigger);

    Physics::Instance().AddRigidBody(m_RigidBody);
}