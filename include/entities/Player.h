#ifndef ROLL_A_BALL_INCLUDE_ENTITIES_PLAYER_H_
#define ROLL_A_BALL_INCLUDE_ENTITIES_PLAYER_H_
#include "Config.h"
#include "Entity.h"

class Player : public Entity
{
public:
    Player(ScenePtr scene);

public:
    void Update();
};

#endif //!ROLL_A_BALL_INCLUDE_ENTITIES_PLAYER_H_