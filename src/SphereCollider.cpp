#include "SphereCollider.h"

SphereCollider::SphereCollider(float radius, const ColliderParameter& parameter)
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

    Physics::Instance().AddRigidBody(m_RigidBody);
}