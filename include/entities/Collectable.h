#ifndef ROLL_A_BALL_INCLUDE_ENTITIES_COLLECTABLE_H_
#define ROLL_A_BALL_INCLUDE_ENTITIES_COLLECTABLE_H_
#include "Config.h"
#include "Entity.h"

class Collectable : public Entity
{
public:
    Collectable(ScenePtr scene);

public:
    void Awake();
    void Update();
    void OnTriggerEnter(const Entity* entity);
};

#endif //!ROLL_A_BALL_INCLUDE_ENTITIES_COLLECTABLE_H_