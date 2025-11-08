#ifndef ROLL_A_BALL_INCLUDE_VECTOR2COMPOSITE_H_
#define ROLL_A_BALL_INCLUDE_VECTOR2COMPOSITE_H_
#include "InputComposite.h"

class Vector2Composite : public InputComposite
{
public:
	Vector2Composite(PathType up, PathType down, PathType left, PathType right)
		:m_Up(up), m_Down(down), m_Left(left), m_Right(right) {}

public:
	bool IsFire(InputContext& context)
	{
		return (context.ReadValue<bool>(m_Up) || context.ReadValue<bool>(m_Down)
			|| context.ReadValue<bool>(m_Left) || context.ReadValue<bool>(m_Right));
	}

	const InputActionCallbackContext& Evaluate(InputContext& context)
	{
		std::cout << "Vector2Composite::Evaluate!!!" << std::endl;

		float up = context.ReadValue<bool>(m_Up) ? 1.0f : 0.0f;
		float down = context.ReadValue<bool>(m_Down) ? -1.0f : 0.0f;
		float left = context.ReadValue<bool>(m_Left) ? -1.0f : 0.0f;
		float right = context.ReadValue<bool>(m_Right) ? 1.0f : 0.0f;

		return InputActionCallbackContext(glm::vec2(right + left, up + down));
	}

private:
	PathType m_Up;
	PathType m_Down;
	PathType m_Left;
	PathType m_Right;
};

#endif //!ROLL_A_BALL_INCLUDE_VECTOR2COMPOSITE_H_