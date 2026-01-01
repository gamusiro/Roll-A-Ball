#include "ParticleSystem.h"

#include "ShaderManager.h"
#include "TimeManager.h"

ParticleSystem::ParticleSystem(const std::shared_ptr<Entity> entity)
	:Component(entity),
	m_playbackTime(0.0f),
	m_delayTime(0.0f),
	m_loopCount(UINT32_MAX),
	m_computeShader(ShaderManager::Instance().GetShader(COMPUTE_SHADER_PARTICLE))
{
	glGenBuffers(1, &m_ssbo);
}

ParticleSystem::~ParticleSystem()
{
	glDeleteBuffers(1, &m_ssbo);
}

void ParticleSystem::Play()
{
	m_isPlay = true;
}

void ParticleSystem::Restart()
{
	m_isPlay = true;
	m_playbackTime = 0.0f;
	m_delayTime = generateStartDelayTime();
}

void ParticleSystem::Pause()
{
	m_isPlay = false;
}

void ParticleSystem::Stop()
{
	m_isPlay = false;
	m_playbackTime = 0.0f;
	m_delayTime = generateStartDelayTime();
}

void ParticleSystem::Update()
{
	// Get delta time
	float dt = TimeManager::Instance().GetDeltaTime();

	if (!m_isPlay)
		return;

	// Loop disable
	if (m_playbackTime >= (m_mainModule.duration + m_delayTime) && !m_mainModule.looping)
	{
		Pause();
		return;
	}

	m_playbackTime += dt;
	m_loopTime = fmodf(m_playbackTime, m_mainModule.duration + m_delayTime);

	// Delay
	if (!isDelayEnded())
		return;

	// Rate over time
	if (glm::abs(m_lastPlaybackTime - m_playbackTime) >= 1.0f)
	{
		m_lastPlaybackTime = glm::floor(m_playbackTime);

		uint32_t num = convertRandomBetweenTwoConstants(m_emissionModule.rateOverTime);
		if(num > 0)
			generateParticle(num);
	}

	uint32_t loopCount = static_cast<uint32_t>(m_playbackTime / (m_mainModule.duration + m_delayTime));
	if (loopCount != m_loopCount && m_mainModule.looping)
	{
		m_loopCount = loopCount;
		m_emissionModule.currentIndex = 0;
	}

	for (uint16_t i = m_emissionModule.currentIndex; i < m_emissionModule.bursts.size(); ++i)
	{
		if (m_emissionModule.bursts[i].time <= (m_loopTime - m_delayTime))
		{
			generateParticle(m_emissionModule.bursts[i].count);
			m_emissionModule.currentIndex++;
		}
	}

	m_computeShader->Bind();

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_ssbo);

	m_computeShader->Set("u_DeltaTime", dt);

	GLuint groups = (m_mainModule.maxParticles + 255) / 256;

	glDispatchCompute(groups, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	m_computeShader->Unbind();
}

void ParticleSystem::SetDuration(float duration)
{
	m_mainModule.duration = duration;
}

void ParticleSystem::SetLooping(bool loop)
{
	m_mainModule.looping = loop;
}

void ParticleSystem::SetStartDelayConstant(float time)
{
	SetStartDelayRandomBetweenTwoConstants(time, time);
}

void ParticleSystem::SetStartDelayRandomBetweenTwoConstants(float minTime, float maxTime)
{
	m_mainModule.startDelay = glm::vec2(minTime, maxTime);
	m_delayTime = generateStartDelayTime();
}

void ParticleSystem::SetStartLifetimeConstant(float time)
{
	SetStartLifetimeRandomBetweenTwoConstants(time, time);
}

void ParticleSystem::SetStartLifetimeRandomBetweenTwoConstants(float minTime, float maxTime)
{
	m_mainModule.startLifetime = glm::vec2(minTime, maxTime);
}

void ParticleSystem::SetStartSpeedConstant(float speed)
{
	SetStartSpeedRandomBetweenTwoConstants(speed, speed);
}

void ParticleSystem::SetStartSpeedRandomBetweenTwoConstants(float minSpeed, float maxSpeed)
{
	m_mainModule.startSpeed = glm::vec2(minSpeed, maxSpeed);
}

void ParticleSystem::SetStartSizeConstant(float size)
{
	SetStartSizeRandomBetweenTwoConstants(size, size);
}

void ParticleSystem::SetStartSizeRandomBetweenTwoConstants(float minSize, float maxSize)
{
	m_mainModule.startSize = glm::vec2(minSize, maxSize);
}

void ParticleSystem::SetStartColor(const glm::vec4& color)
{
	m_mainModule.startColor = color;
}

void ParticleSystem::SetGravityModifierConstant(float gravity)
{
	SetGravityModifierRandomBetweenTwoConstants(gravity, gravity);
}

void ParticleSystem::SetGravityModifierRandomBetweenTwoConstants(float minGravity, float maxGravity)
{
	m_mainModule.gravityModifier = glm::vec2(minGravity, maxGravity);
}

void ParticleSystem::SetMaxParticles(uint32_t num)
{
	m_mainModule.maxParticles = num;
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Particle) * num, nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ParticleSystem::SetRateOverTimeConstant(uint32_t num)
{
	SetRateOverTimeRandomBetweenTwoConstants(num, num);
}

void ParticleSystem::SetRateOverTimeRandomBetweenTwoConstants(uint32_t minNum, uint32_t maxNum)
{
	m_emissionModule.rateOverTime = glm::vec2(minNum, maxNum);
}

void ParticleSystem::AddBurst(float time, uint32_t count, uint32_t cycles, float interval)
{
	if (time >= m_mainModule.duration)
		return;

	if (count > m_mainModule.maxParticles)
		return;

	for (uint32_t i = 0; i < cycles; ++i)
	{
		float targetTime = time + float(interval * i);
		if (targetTime >= m_mainModule.duration)
			return;
		m_emissionModule.bursts.push_back({ targetTime, count });
	}
	std::sort(m_emissionModule.bursts.begin(), m_emissionModule.bursts.end());
}

void ParticleSystem::SetShapeSphere(float radius)
{
	m_shapeModule.shape = ShapeType::Sphere;
	m_shapeModule.radius = glm::max(0.1f, radius);
}

void ParticleSystem::SetShapeBox(const glm::vec3& size)
{
	m_shapeModule.shape = ShapeType::Box;
	m_shapeModule.boxSize = glm::max(glm::vec3(0.1f), size);
}

void ParticleSystem::SetColorOverLifetime(const std::string& filename)
{
	m_colorOverLifetime.imageName = filename;
}

const std::string& ParticleSystem::GetColorOverLifetime() const
{
	return m_colorOverLifetime.imageName;
}

void ParticleSystem::generateParticle(uint32_t num)
{
	// Over max particles
	if ((num > m_mainModule.maxParticles)
		|| (num <= 0))
		return;

	std::vector<Particle> particles(num);
	for (auto& particle : particles)
	{
		generateParticlePosition(particle.position);
		generateParticleVelocity(particle.position, particle.velocity);
		particle.color = m_mainModule.startColor;
		particle.life = convertRandomBetweenTwoConstants(m_mainModule.startLifetime);
		particle.size = convertRandomBetweenTwoConstants(m_mainModule.startSize);

		float gravityStrength = convertRandomBetweenTwoConstants(m_mainModule.gravityModifier);
		particle.accel = glm::vec3(0.0f, -9.81f * gravityStrength, 0.0f);
		particle.drag = 0.15f;
		particle.maxLife = particle.life;
	}

	// calcurate max index
	uint32_t maxIndex = m_nextWriteIndex + num;
	bool isOver = maxIndex > m_mainModule.maxParticles;

	if (isOver)
	{
		uint32_t nextWriteCount = maxIndex - m_mainModule.maxParticles;
		uint32_t size1 = sizeof(Particle) * (num - nextWriteCount);
		uint32_t offset1 = sizeof(Particle) * m_nextWriteIndex;

		uint32_t size2 = sizeof(Particle) * nextWriteCount;
		uint32_t offset2 = 0;

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset1, size1, &particles[0]);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset2, size2, &particles[nextWriteCount]);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
	else
	{
		uint32_t size = sizeof(Particle) * num;
		uint32_t offset = sizeof(Particle) * m_nextWriteIndex;
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, particles.data());
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
	m_nextWriteIndex = (m_nextWriteIndex + num) % m_mainModule.maxParticles;
}

void ParticleSystem::generateParticlePosition(glm::vec3& position)
{
	switch (m_shapeModule.shape)
	{
	case ShapeType::Sphere:
		glm::vec3 v = glm::normalize(glm::linearRand(glm::vec3(-1), glm::vec3(1)));
		position = v * cbrt(glm::linearRand(0.0f, 1.0f)) * m_shapeModule.radius;
		break;
	case ShapeType::Box:
		glm::vec3 size = m_shapeModule.boxSize;
		position = glm::linearRand(-size * 0.5f, size * 0.5f);
		break;
	}
}

void ParticleSystem::generateParticleVelocity(const glm::vec3& position, glm::vec3& velocity)
{
	float len = position.length();
	glm::vec3 dir;
	if (len == 0.0f)
		dir = glm::normalize(glm::linearRand(glm::vec3(-1), glm::vec3(1)));
	else
		dir = glm::normalize(position);

	float speed = convertRandomBetweenTwoConstants(m_mainModule.startSpeed);
	velocity = dir * speed;
}

float ParticleSystem::generateStartDelayTime()
{
	return convertRandomBetweenTwoConstants(m_mainModule.startDelay);
}

bool ParticleSystem::isDelayEnded() const
{
	return m_loopTime >= m_delayTime;
}

float ParticleSystem::convertRandomBetweenTwoConstants(const glm::vec2& val)
{
	return glm::linearRand(val.x, val.y);
}