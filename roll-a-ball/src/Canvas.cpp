#include "Canvas.h"

#include "RectTransform.h"
#include "Transform.h"

Canvas::Canvas(const std::shared_ptr<Entity> entity)
	:Component(entity),
	m_RenderCamera(nullptr)
{
}

Canvas::~Canvas()
{
}

void Canvas::SetScreenSpaceOverlay()
{
	m_RenderMode = RenderMode::SCREENSPACE_OVERLAY;
	m_RenderCamera = nullptr;
}

void Canvas::SetScreenSpaceCamera(Transform* cameraTransform)
{
	m_RenderMode = RenderMode::SCREENSPACE_CAMERA;
	m_RenderCamera = cameraTransform;
}

void Canvas::SetWorldSpace()
{
	m_RenderMode = RenderMode::WORLDSPACE;
	m_RenderCamera = nullptr;
}

const glm::mat4 Canvas::GetProjection(const RectTransform& transform) const
{
	glm::mat4 ret = glm::mat4(1.0f);
	switch (m_RenderMode)
	{
	case Canvas::RenderMode::SCREENSPACE_OVERLAY:
		ret = generateProjectionScreenSpaceOverlay(transform);
		break;
	case Canvas::RenderMode::SCREENSPACE_CAMERA:
		ret = generateProjectionScreenSpaceCamera(transform);
		break;
	case Canvas::RenderMode::WORLDSPACE:
		break;
	}

	return ret;
}

const glm::mat4 Canvas::generateProjectionScreenSpaceOverlay(const RectTransform& transform) const
{
	float left = 0.0f;
	float right = transform.GetSize().x;
	float top = transform.GetSize().y;
	float bottom = 0.0f;
	return glm::ortho(left, right, bottom, top);	// Orthographic projection: origin at left-bottom (match Unity coordinates)
}

const glm::mat4 Canvas::generateProjectionScreenSpaceCamera(const RectTransform& transform) const
{
	float left = 0.0f;
	float right = transform.GetSize().x;
	float top = transform.GetSize().y;
	float bottom = 0.0f;
	float camNear = -1.0f;
	float camFar = 1.0f;

	glm::vec3 pos = m_RenderCamera->GetPosition();
	return glm::ortho(left, right, bottom, top, camNear, camFar) * glm::translate(glm::mat4(1.0f), glm::vec3(- pos.x, -pos.y, 0.0f));
}
