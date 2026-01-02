#ifndef ROLL_A_BALL_INCLUDE_TRANSFORM_H_
#define ROLL_A_BALL_INCLUDE_TRANSFORM_H_
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Component.h"

class Transform : public Component
{
public:
	Transform(const std::shared_ptr<Entity> entity)
		: Component(entity),
		m_Parent(nullptr),
		m_Position(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_Rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_Scale(glm::vec3(1.0f, 1.0f, 1.0f))
	{
		calculate();
	}

	Transform(const std::shared_ptr<Entity> entity, Transform* parent)
		: Component(entity),
		m_Parent(parent),
		m_Position(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_Rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_Scale(glm::vec3(1.0f, 1.0f, 1.0f))
	{
		calculate();
	}

	Transform(const std::shared_ptr<Entity> entity, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
		: Component(entity),
		m_Parent(nullptr),
		m_Position(position),
		m_Rotation(rotation),
		m_Scale(scale)
	{
		calculate();
	}

	Transform(const std::shared_ptr<Entity> entity, const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
		: Component(entity),
		m_Parent(nullptr),
		m_Position(position),
		m_Rotation(rotation),
		m_Scale(scale)
	{
		calculate();
	}

	Transform(const std::shared_ptr<Entity> entity, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, Transform* parent)
		: Component(entity),
		m_Parent(parent),
		m_Position(position),
		m_Rotation(rotation),
		m_Scale(scale)
	{
		calculate();
	}

	Transform(const std::shared_ptr<Entity> entity, const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale, Transform* parent)
		: Component(entity),
		m_Parent(parent),
		m_Position(position),
		m_Rotation(rotation),
		m_Scale(scale)
	{
		calculate();
	}

public:
	inline const glm::vec3 GetPosition() const { return m_Position; }
	inline const glm::vec3 GetRotationEuler() const { return glm::degrees(glm::eulerAngles(m_Rotation)); }
	inline const glm::quat GetRotationQuat() const { return m_Rotation; }
	inline const glm::vec3 GetScale () const { return m_Scale; }
	inline const glm::vec3 GetForward() const { return m_ForwardDir; }
	inline const glm::vec3 GetRight() const { return m_RightDir; }
	inline const glm::vec3 GetUp() const { return m_UpDir; }
	inline const glm::mat4 GetLocalMatrix() const { return m_LocalMatrix; }
	inline const glm::mat4 GetWorldMatrix() const { return m_WorldMatrix; }
	inline const Transform* GetParent() const { return m_Parent; }
	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& euler);
	void SetRotation(const glm::quat& quat);
	void SetScale (const glm::vec3& scale);
	void SetParent(Transform* parent);

private:
	void calculate();
	void calclateParent(glm::mat4 parent);

private:
	Transform* m_Parent;
	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_Scale;

	glm::vec3 m_ForwardDir;
	glm::vec3 m_RightDir;
	glm::vec3 m_UpDir;

	glm::mat4 m_LocalMatrix = glm::mat4(1.0f);
	glm::mat4 m_WorldMatrix = glm::mat4(1.0f);

	std::vector<Transform*> m_Children;
};

#endif //!ROLL_A_BALL_INCLUDE_TRANSFORM_H_