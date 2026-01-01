#ifndef ROLL_A_BALL_INCLUDE_PARTICLE_SYSTEM_H_
#define ROLL_A_BALL_INCLUDE_PARTICLE_SYSTEM_H_
#include "Config.h"

#include "Component.h"

class ParticleSystem : public Component
{
	private:
	enum class ShapeType
	{
		Sphere,
		Box
	};

	struct Particle
	{
		glm::vec3 position = glm::vec3(-999999.0f); float life = -1.0f;
		glm::vec3 velocity; float size;
		glm::vec4 color;
		glm::vec3 accel; float drag;
		glm::vec3 offset; float maxLife;
	};

	struct MainModule
	{
		float duration = 5.0f;
		bool looping = true;
		glm::vec2 startDelay = glm::vec2(0.0f);
		glm::vec2 startLifetime = glm::vec2(5.0f);
		glm::vec2 startSpeed = glm::vec2(5.0f);
		glm::vec2 startSize = glm::vec2(1.0f);
		glm::vec4 startColor = glm::vec4(1.0f);
		glm::vec2 gravityModifier = glm::vec2(0.0f);
		uint32_t maxParticles = 1000;
	};

	struct EmissionModule
	{
		struct Burst
		{
			float time;
			uint32_t count;
			bool operator<(const Burst& other) const { return time < other.time; }
		};

		glm::vec2 rateOverTime = glm::vec2(0.0f);
		std::vector<Burst> bursts;
		uint16_t currentIndex = 0;
	};

	struct ShapeModule
	{
		ShapeType shape = ShapeType::Sphere;
		glm::vec3 boxSize = glm::vec3(1.0f);
		float radius = 1.0f;
	};

	struct ColorOverLifetimeModule
	{
		std::string imageName;
	};

public:
	ParticleSystem(const std::shared_ptr<Entity> entity);
	~ParticleSystem();

public:
	void Play();
	void Restart();
	void Pause();
	void Stop();
	void Update();

public:
	void SetDuration(float duration);
	void SetLooping(bool loop);
	void SetStartDelayConstant(float time);
	void SetStartDelayRandomBetweenTwoConstants(float minTime, float maxTime);
	void SetStartLifetimeConstant(float time);
	void SetStartLifetimeRandomBetweenTwoConstants(float minTime, float maxTime);
	void SetStartSpeedConstant(float speed);
	void SetStartSpeedRandomBetweenTwoConstants(float minSpeed, float maxSpeed);
	void SetStartSizeConstant(float size);
	void SetStartSizeRandomBetweenTwoConstants(float minSize, float maxSize);
	void SetStartColor(const glm::vec4& color);
	void SetGravityModifierConstant(float gravity);
	void SetGravityModifierRandomBetweenTwoConstants(float minGravity, float maxGravity);
	void SetMaxParticles(uint32_t num);

public:
	void SetRateOverTimeConstant(uint32_t num);
	void SetRateOverTimeRandomBetweenTwoConstants(uint32_t minNum, uint32_t maxNum);
	void AddBurst(float time, uint32_t count, uint32_t cycles, float interval);

public:
	void SetShapeSphere(float radius);
	void SetShapeBox(const glm::vec3& size);

public:
	void SetColorOverLifetime(const std::string& filename);
	const std::string& GetColorOverLifetime() const;

private:
	void generateParticle(uint32_t num);
	void generateParticlePosition(glm::vec3& position);
	void generateParticleVelocity(const glm::vec3& position, glm::vec3& velocity);
	float generateStartDelayTime();

private:
	bool isDelayEnded() const;

private:
	float convertRandomBetweenTwoConstants(const glm::vec2& val);

private:
	MainModule m_mainModule;
	EmissionModule m_emissionModule;
	ShapeModule m_shapeModule;
	ColorOverLifetimeModule m_colorOverLifetime;

private:
	uint32_t m_ssbo;
	ShaderPtr m_computeShader;

	float m_lastPlaybackTime;
	float m_playbackTime;
	float m_loopTime;
	float m_delayTime;

	uint32_t m_nextWriteIndex = 0;
	uint32_t m_loopCount;

	bool m_isPlay = false;

private:
	friend class ParticleRenderer;
};

#endif //! ROLL_A_BALL_INCLUDE_PARTICLE_SYSTEM_H_