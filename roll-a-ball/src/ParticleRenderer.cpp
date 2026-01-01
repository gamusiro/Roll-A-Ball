#include "ParticleRenderer.h"
#include "ParticleSystem.h"

ParticleRenderer::ParticleRenderer(const std::shared_ptr<Entity> entity)
    :Component(entity)
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
}

ParticleRenderer::~ParticleRenderer()
{
    glDeleteVertexArrays(1, &m_VAO);
}

void ParticleRenderer::Render(const ParticleSystem& ps) const
{
    if (!ps.m_isPlay)
	    return;

    if (!ps.isDelayEnded())
        return;

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ps.m_ssbo);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ps.m_ssbo);
    glDrawArrays(GL_POINTS, 0, ps.m_mainModule.maxParticles);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}