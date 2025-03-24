#ifndef ROLL_A_BALL_INCLUDE_RIGIDBODY_H_
#define ROLL_A_BALL_INCLUDE_RIGIDBODY_H_
#include "Config.h"

#include "Collider.h"
#include "Utils.h"

class RigidBody
{
public:
    RigidBody(const Collider& collider);

public:
    void AddImpulse(const glm::vec3& impulse);

    inline const glm::vec3 GetPosition() const { return VEC3_BT_2_GLM(m_RigidBody->getWorldTransform().getOrigin()); }

private:
    btRigidBody* m_RigidBody;
};

#endif //!ROLL_A_BALL_INCLUDE_RIGIDBODY_H_