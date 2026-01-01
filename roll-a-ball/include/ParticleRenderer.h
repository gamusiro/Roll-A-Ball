#ifndef ROLL_A_BALL_INCLUDE_PARTICLE_RENDERER_H_
#define ROLL_A_BALL_INCLUDE_PARTICLE_RENDERER_H_
#include "Config.h"

#include "Component.h"

class ParticleSystem;
class ParticleRenderer : public Component
{
public:
	ParticleRenderer(const std::shared_ptr<Entity> entity);
	~ParticleRenderer();

public:
    void Render(const ParticleSystem& ps) const;

private:
    uint32_t m_VAO;
};

#endif //! ROLL_A_BALL_INCLUDE_PARTICLE_RENDERER_H_