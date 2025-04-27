#ifndef ROLL_A_BALL_INCLUDE_BOXCOLLIDER_H_
#define ROLL_A_BALL_INCLUDE_BOXCOLLIDER_H_
#include "Config.h"

#include "Collider.h"

class BoxCollider : public Collider
{
public:
    BoxCollider(const Entity* entity, const glm::vec3& scale, const ColliderParameter& parameter);
};

#endif //!ROLL_A_BALL_INCLUDE_BOXCOLLIDER_H_