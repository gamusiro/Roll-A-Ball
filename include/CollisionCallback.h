#ifndef ROLL_A_BALL_INCLUDE_COLLISIONCALLBACK_H_ 
#define ROLL_A_BALL_INCLUDE_COLLISIONCALLBACK_H_
#include "Config.h"

class CollisionCallback : public btCollisionWorld::ContactResultCallback
{
public:
    btScalar addSingleResult(
        btManifoldPoint& cp,
        const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0,
        const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) override;
};

#endif //!ROLL_A_BALL_INCLUDE_COLLISIONCALLBACK_H_