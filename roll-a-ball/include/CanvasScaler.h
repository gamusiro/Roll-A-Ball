#ifndef ROLL_A_BALL_INCLUDE_CANVASSCALER_H_
#define ROLL_A_BALL_INCLUDE_CANVASSCALER_H_
#include "Config.h"

#include "Component.h"

class CanvasScaler : public Component
{
public:
	enum class ScaleMode
	{
		CONSTANT_PIXEL_SIZE,
		SCALE_WITH_SCREEN_SIZE,
		CONSTANT_PHYSICAL_SIZE
	};

	enum class ScreenMatchMode
	{
		MATCH_WIDTH_OR_HEIGHT,
		EXPAND,
		SHRINK
	};

public:
	CanvasScaler(const std::shared_ptr<Entity> entity);
	~CanvasScaler();

public:
	void SetScaleFactor(float scale);
	void SetScaleFactor(const glm::vec2& currentResolution);
	void SetConstantPixelSize(float scaleFactor, float pixelsPerUnit);
	void SetScaleWithScreenSizeMatchWidthOrHeight(const glm::vec2& resolution, float match, float pixelsPerUnit);
	void SetScaleWithScreenSizeExpand(const glm::vec2& resolution, float pixelsPerUnit);
	void SetScaleWithScreenSizeShrink(const glm::vec2& resolution, float pixelsPerUnit);

	inline float GetScaleFactor() const { return m_ScaleFactor; }

private:
	ScaleMode m_ScaleMode;
	ScreenMatchMode m_ScreenMatchMode;
	glm::vec2 m_ReferenceResolution;
	float m_ScaleFactor;
	float m_MatchFactor;
	float m_ReferencePixelsPerUnit;
};

#endif //!ROLL_A_BALL_INCLUDE_CANVASSCALER_H_