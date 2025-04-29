#ifndef ROLL_A_BALL_INCLUDE_ENTITIES_GROUND_H_
#define ROLL_A_BALL_INCLUDE_ENTITIES_GROUND_H_
#include "Config.h"
#include "Entity.h"

class Ground : public Entity
{
public:
    Ground(ScenePtr scene);

public:
    void Awake();
};

#endif //!ROLL_A_BALL_INCLUDE_ENTITIES_GROUND_H_