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
    bool isTrigger = false;
} ColliderParameter;

class Collider : public Component
{
public:
    Collider(const Entity* entity);
    virtual ~Collider();

public:
    void SetTrigger(bool isTrigger);
    bool IsTrigger() const;

protected:
    btCollisionShape* m_Shape;
    btRigidBody* m_RigidBody;

private:
    friend class Physics;
    friend class RigidBody;
};

#endif //!ROLL_A_BALL_INCLUDE_COLLIDER_H_