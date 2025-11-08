#ifndef ROLL_A_BALL_INCLUDE_INPUTPATH_H_
#define ROLL_A_BALL_INCLUDE_INPUTPATH_H_
#include "Config.h"

#include "InputAction.h"

class InputPath
{
public:
	enum class Keyboard
	{
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		SPACE, ENTER
	};
	enum class Mouse
	{
		LEFT, RIGHT
	};

public:
	static int ConvertPathType(InputPath::Keyboard key)
	{
		int ret = -1;
		switch (key)
		{
		case InputPath::Keyboard::A:
			ret = GLFW_KEY_A;
			break;
		case InputPath::Keyboard::B:
			ret = GLFW_KEY_B;
			break;
		case InputPath::Keyboard::C:
			ret = GLFW_KEY_C;
			break;
		case InputPath::Keyboard::D:
			ret = GLFW_KEY_D;
			break;
		case InputPath::Keyboard::E:
			ret = GLFW_KEY_E;
			break;
		case InputPath::Keyboard::F:
			ret = GLFW_KEY_F;
			break;
		case InputPath::Keyboard::G:
			ret = GLFW_KEY_G;
			break;
		case InputPath::Keyboard::H:
			ret = GLFW_KEY_H;
			break;
		case InputPath::Keyboard::I:
			ret = GLFW_KEY_I;
			break;
		case InputPath::Keyboard::J:
			ret = GLFW_KEY_J;
			break;
		case InputPath::Keyboard::K:
			ret = GLFW_KEY_K;
			break;
		case InputPath::Keyboard::L:
			ret = GLFW_KEY_L;
			break;
		case InputPath::Keyboard::M:
			ret = GLFW_KEY_M;
			break;
		case InputPath::Keyboard::N:
			ret = GLFW_KEY_N;
			break;
		case InputPath::Keyboard::O:
			ret = GLFW_KEY_O;
			break;
		case InputPath::Keyboard::P:
			ret = GLFW_KEY_P;
			break;
		case InputPath::Keyboard::Q:
			ret = GLFW_KEY_Q;
			break;
		case InputPath::Keyboard::R:
			ret = GLFW_KEY_R;
			break;
		case InputPath::Keyboard::S:
			ret = GLFW_KEY_S;
			break;
		case InputPath::Keyboard::T:
			ret = GLFW_KEY_T;
			break;
		case InputPath::Keyboard::U:
			ret = GLFW_KEY_U;
			break;
		case InputPath::Keyboard::V:
			ret = GLFW_KEY_V;
			break;
		case InputPath::Keyboard::W:
			ret = GLFW_KEY_W;
			break;
		case InputPath::Keyboard::X:
			ret = GLFW_KEY_X;
			break;
		case InputPath::Keyboard::Y:
			ret = GLFW_KEY_Y;
			break;
		case InputPath::Keyboard::Z:
			ret = GLFW_KEY_Z;
			break;
		case InputPath::Keyboard::SPACE:
			ret = GLFW_KEY_SPACE;
			break;
		case InputPath::Keyboard::ENTER:
			ret = GLFW_KEY_ENTER;
			break;
		default:
			break;
		}
		return ret;
	}

	static int ConvertPathType(InputPath::Mouse btn)
	{
		int ret = -1;
		switch (btn)
		{
		case InputPath::Mouse::LEFT:
			ret = GLFW_MOUSE_BUTTON_LEFT;
			break;
		case InputPath::Mouse::RIGHT:
			ret = GLFW_MOUSE_BUTTON_RIGHT;
			break;
		default:
			break;
		}
		return ret;
	}
};

using PathType = std::variant<InputPath::Keyboard, InputPath::Mouse>;

#endif //!ROLL_A_BALL_INCLUDE_INPUTPATH_H_