#ifndef ROLL_A_BALL_INCLUDE_CAMERA_H_
#define ROLL_A_BALL_INCLUDE_CAMERA_H_
#include "Config.h"

#include "Transform.h"
#include "Component.h"

class Camera : public Component
{
protected:
	Camera(const std::shared_ptr<Entity> entity) : Component(entity) {}

public:
	virtual ~Camera() = default;
    inline const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }

public:
	static const glm::mat4 CalcViewMatrix(const Transform& transform);
	static const glm::mat4 CalcViewMatrix(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up);

protected:
    virtual void calculate() = 0;

protected:
    glm::mat4 m_ProjectionMatrix;
};

class OrthographicsCamera : public Camera
{
public:
	OrthographicsCamera(const std::shared_ptr<Entity> entity);
	OrthographicsCamera(const std::shared_ptr<Entity> entity, float left, float right, float bottom, float top);
	~OrthographicsCamera() = default;

protected:
	void calculate() override;

private:
	float m_Left;
	float m_Right;
	float m_Bottom;
	float m_Top;
};

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(const std::shared_ptr<Entity> entity);
	PerspectiveCamera(const std::shared_ptr<Entity> entity, float fovy, float aspect, float znear, float zfar);
	~PerspectiveCamera() = default;

	inline void SetFovy(float fovy) 
	{ 
		m_Fovy = fovy;
		calculate();
	}

	inline void SetAspect(float aspect) 
	{ 
		m_Aspect = aspect;
		calculate();
	}

	inline void SetAspect(float width, float height) 
	{ 
		SetAspect(width / height);
	}

	inline void SetNearZ(float znear) 
	{ 
		m_Znear = znear;
		calculate();
	}

	inline void SetFarZ(float zfar) 
	{ 
		m_Zfar = zfar;
		calculate();
	}

protected:
	void calculate() override;

private:
	float m_Fovy;
	float m_Aspect;
	float m_Znear;
	float m_Zfar;
};

#endif //!ROLL_A_BALL_INCLUDE_CAMERA_H_