#ifndef ROLL_A_BALL_INCLUDE_INPUTCONTEXT_H_
#define ROLL_A_BALL_INCLUDE_INPUTCONTEXT_H_
#include "Config.h"

#include "InputManager.h"
#include "InputPath.h"

class InputContext
{
public:
	InputContext(InputManager& im) 
		: m_InputManager(im) {}

	template<typename T>
	T ReadValue(PathType path)
	{
		if (auto val = std::get_if<InputPath::Keyboard>(&path))
		{
			return m_InputManager.GetKey(InputPath::ConvertPathType(*val));
		}
		else if (auto val = std::get_if<InputPath::Mouse>(&path))
		{
			return m_InputManager.GetMouse(InputPath::ConvertPathType(*val));
		}
		else
		{
			throw std::runtime_error("Unsupported type requested for ReadValue.");
		}
	}

private:
	InputManager& m_InputManager;
};

#endif //!ROLL_A_BALL_INCLUDE_INPUTCONTEXT_H_