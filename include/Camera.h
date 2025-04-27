#ifndef ROLL_A_BALL_INCLUDE_CAMERA_H_
#define ROLL_A_BALL_INCLUDE_CAMERA_H_
#include "Config.h"

#include "Transform.h"
#include "Component.h"

class Camera : public Component
{
protected:
	Camera(const Entity* entity) : Component(entity) {}

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
	OrthographicsCamera(const Entity* entity);
	OrthographicsCamera(const Entity* entity, float left, float right, float bottom, float top);
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
	PerspectiveCamera(const Entity* entity);
	PerspectiveCamera(const Entity* entity, float fovy, float aspect, float znear, float zfar);
	~PerspectiveCamera() = default;

protected:
	void calculate() override;

private:
	float m_Fovy;
	float m_Aspect;
	float m_Znear;
	float m_Zfar;
};

#endif //!ROLL_A_BALL_INCLUDE_CAMERA_H_