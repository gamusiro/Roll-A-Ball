#ifndef ROLL_A_BALL_INCLUDE_COLLIDER_H_
#define ROLL_A_BALL_INCLUDE_COLLIDER_H_
#include "Config.h"

#include "Utils.h"
#include "Physics.h"
#include "Component.h"

typedef struct
{
    btTransform transform;
    float mass;
    float friction;
} ColliderParameter;

class Collider : public Component
{
public:
    Collider(const Entity* entity);
    virtual ~Collider();

protected:
    btCollisionWorld::ContactResultCallback* m_Callback;
    btCollisionShape* m_Shape;
    btRigidBody* m_RigidBody;

private:
    friend class Physics;
    friend class RigidBody;
};

#endif //!ROLL_A_BALL_INCLUDE_COLLIDER_H_