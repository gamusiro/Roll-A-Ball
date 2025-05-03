#ifndef ROLL_A_BALL_INCLUDE_APPLICATIONEVENT_H_
#define ROLL_A_BALL_INCLUDE_APPLICATIONEVENT_H_

class WindowResizeEvent
{
public:
	WindowResizeEvent(int width, int height)
		:m_Width(width), m_Height(height) {}

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	int m_Width;
	int m_Height;
};

#endif //!ROLL_A_BALL_INCLUDE_APPLICATIONEVENT_H_