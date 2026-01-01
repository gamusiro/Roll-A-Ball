#ifndef ROLL_A_BALL_INCLUDE_ENTITIES_BURST_PARTICLE_H_
#define ROLL_A_BALL_INCLUDE_ENTITIES_BURST_PARTICLE_H_
#include "Config.h"
#include "Entity.h"

class BurstParticle : public Entity
{
public:
    BurstParticle(ScenePtr scene);

public:
    void Awake();

public:
    void Burst();

private:
    bool m_IsFired = false;
};

#endif //!ROLL_A_BALL_INCLUDE_ENTITIES_BURST_PARTICLE_H_