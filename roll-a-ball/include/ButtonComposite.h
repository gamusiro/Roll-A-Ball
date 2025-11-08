#ifndef ROLL_A_BALL_INCLUDE_BUTTONCOMPOSITE_H_
#define ROLL_A_BALL_INCLUDE_BUTTONCOMPOSITE_H_
#include "InputComposite.h"

class ButtonComposite : public InputComposite
{
public:
	ButtonComposite(PathType type)
		:m_PathType(type) {}

public:
	bool IsFire(InputContext& context)
	{
		return context.ReadValue<bool>(m_PathType);
	}

	const InputActionCallbackContext& Evaluate(InputContext& context)
	{
		std::cout << "ButtonComposite::Evaluate!!!" << std::endl;
		return InputActionCallbackContext(context.ReadValue<bool>(m_PathType));
	}

private:
	PathType m_PathType;
};

#endif //!ROLL_A_BALL_INCLUDE_BUTTONCOMPOSITE_H_