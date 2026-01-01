#include "entities/BurstParticle.h"

#include "Scene.h"
#include "Logger.h"
#include "ShaderManager.h"

BurstParticle::BurstParticle(ScenePtr scene)
    : Entity(scene)
{
}

void BurstParticle::Awake()
{   
    ShaderManager& sm = ShaderManager::Instance();
    Material& material = AddComponent<Material>();
    material.SetShader(sm.GetShader(RENDERER_SHADER_PARTRICLE));

    AddComponent<ParticleRenderer>();

    ParticleSystem& ps = AddComponent<ParticleSystem>();
    ps.SetDuration(5.0f);
    ps.SetLooping(true);
    ps.SetStartDelayConstant(0.0f);
    ps.SetStartLifetimeConstant(5.0f);
    ps.SetStartSpeedConstant(5.0f);
    ps.SetStartSizeConstant(0.2f);
    ps.SetStartColor(glm::vec4(1.0f));
    ps.SetGravityModifierConstant(0.1f);
    ps.SetMaxParticles(1000);
    ps.SetRateOverTimeConstant(100);
    ps.SetShapeSphere(5.0f);
}

void BurstParticle::Burst()
{
    if (!m_IsFired)
    {
        ParticleSystem& ps = GetComponent<ParticleSystem>();
        ps.Play();
        m_IsFired = true;
    }
}