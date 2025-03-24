#ifndef ROLL_A_BALL_INCLUDE_SHPERECOLLIDER_H_
#define ROLL_A_BALL_INCLUDE_SHPERECOLLIDER_H_
#include "Config.h"

#include "Collider.h"

class SphereCollider : public Collider
{
public:
    SphereCollider(float radius, const ColliderParameter& parameter);
};

#endif //!ROLL_A_BALL_INCLUDE_SHPERECOLLIDER_H_