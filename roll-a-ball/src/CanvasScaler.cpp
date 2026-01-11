#include "CanvasScaler.h"

CanvasScaler::CanvasScaler(const std::shared_ptr<Entity> entity)
	:Component(entity)
{
}

CanvasScaler::~CanvasScaler()
{
}

void CanvasScaler::SetScaleFactor(float scale)
{
	m_ScaleFactor = scale;
}

void CanvasScaler::SetScaleFactor(const glm::vec2& currentResolution)
{
	if (m_ScaleMode != ScaleMode::SCALE_WITH_SCREEN_SIZE)
		return;

	float widthScale = currentResolution.x / m_ReferenceResolution.x;
	float heightScale = currentResolution.y / m_ReferenceResolution.y;

	m_ScaleFactor = glm::mix(widthScale, heightScale, m_MatchFactor);
}

void CanvasScaler::SetConstantPixelSize(float scaleFactor, float pixelsPerUnit)
{
	m_ScaleMode = ScaleMode::CONSTANT_PIXEL_SIZE;
	m_ScaleFactor = scaleFactor;
	m_ReferencePixelsPerUnit = pixelsPerUnit;
}

void CanvasScaler::SetScaleWithScreenSizeMatchWidthOrHeight(const glm::vec2& resolution, float match, float pixelsPerUnit)
{
	m_ReferenceResolution = resolution;
	m_ScaleMode = ScaleMode::SCALE_WITH_SCREEN_SIZE;
	m_ScreenMatchMode = ScreenMatchMode::MATCH_WIDTH_OR_HEIGHT;
	m_ReferencePixelsPerUnit = pixelsPerUnit;
	m_MatchFactor = match;
}

void CanvasScaler::SetScaleWithScreenSizeExpand(const glm::vec2& resolution, float pixelsPerUnit)
{
	m_ReferenceResolution = resolution;
	m_ScaleMode = ScaleMode::SCALE_WITH_SCREEN_SIZE;
	m_ScreenMatchMode = ScreenMatchMode::EXPAND;
	m_ReferencePixelsPerUnit = pixelsPerUnit;
}

void CanvasScaler::SetScaleWithScreenSizeShrink(const glm::vec2& resolution, float pixelsPerUnit)
{
	m_ReferenceResolution = resolution;
	m_ScaleMode = ScaleMode::SCALE_WITH_SCREEN_SIZE;
	m_ScreenMatchMode = ScreenMatchMode::SHRINK;
	m_ReferencePixelsPerUnit = pixelsPerUnit;
}
