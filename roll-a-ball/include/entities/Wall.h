#ifndef ROLL_A_BALL_INCLUDE_ENTITIES_WALL_H_
#define ROLL_A_BALL_INCLUDE_ENTITIES_WALL_H_
#include "Config.h"
#include "Entity.h"

class Wall : public Entity
{
public:
    Wall(ScenePtr scene);

public:
    void Awake();
};

#endif //!ROLL_A_BALL_INCLUDE_ENTITIES_WALL_H_