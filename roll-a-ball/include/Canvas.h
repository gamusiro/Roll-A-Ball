#ifndef ROLL_A_BALL_INCLUDE_CANVAS_H_
#define ROLL_A_BALL_INCLUDE_CANVAS_H_
#include "Config.h"

#include "Component.h"

class RectTransform;
class Transform;
class Canvas : public Component
{
public:
	enum class RenderMode
	{
		SCREENSPACE_OVERLAY,
		SCREENSPACE_CAMERA,
		WORLDSPACE
	};

public:
    Canvas(const std::shared_ptr<Entity> entity);
    ~Canvas();

public:
	void SetScreenSpaceOverlay();
	void SetScreenSpaceCamera(Transform* cameraTransform);
	void SetWorldSpace();

	const glm::mat4 GetProjection(const RectTransform& transform) const;

private:
	const glm::mat4 generateProjectionScreenSpaceOverlay(const RectTransform& transform) const;
	const glm::mat4 generateProjectionScreenSpaceCamera(const RectTransform& transform) const;

private:
	RenderMode m_RenderMode = RenderMode::SCREENSPACE_OVERLAY;
	Transform* m_RenderCamera;
};

#endif //!ROLL_A_BALL_INCLUDE_CANVAS_H_