#ifndef ROLL_A_BALL_INCLUDE_RIGIDBODY_H_
#define ROLL_A_BALL_INCLUDE_RIGIDBODY_H_
#include "Config.h"

#include "Collider.h"
#include "Utils.h"
#include "Component.h"

class RigidBody : public Component
{
public:
    RigidBody(const Entity* entity, const Collider& collider);

public:
    void AddImpulse(const glm::vec3& impulse);
    inline const glm::vec3 GetPosition() const 
    {
        return VEC3_BT_2_GLM(m_RigidBody->getWorldTransform().getOrigin()); 
    }
    
    inline const glm::quat GetRotation() const 
    {
        btQuaternion quat = m_RigidBody->getWorldTransform().getRotation();
        return QUAT_BT_2_GLM(quat);
    }

    inline void SetPosition(const glm::vec3& position) 
    { 
        btTransform transform = m_RigidBody->getWorldTransform();
        transform.setOrigin(VEC3_GLM_2_BT(position));
        m_RigidBody->setWorldTransform(transform);
    }

    inline void SetRotation(const glm::quat& quat)
    {
        btTransform transform = m_RigidBody->getWorldTransform();
        transform.setRotation(QUAT_GLM_2_BT(quat));
        m_RigidBody->setWorldTransform(transform);
    }

private:
    btRigidBody* m_RigidBody;
};

#endif //!ROLL_A_BALL_INCLUDE_RIGIDBODY_H_