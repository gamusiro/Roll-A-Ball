#ifndef ROLL_A_BALL_INCLUDE_INPUTACTIONCALLBACKCONTEXT_H_
#define ROLL_A_BALL_INCLUDE_INPUTACTIONCALLBACKCONTEXT_H_
#include "Config.h"

using ValueType = std::variant<bool, float, glm::vec2>;

class InputActionCallbackContext
{
public:
	InputActionCallbackContext(ValueType val)
		:m_Value(val) {}

	template<typename T>
	T ReadValue() const
	{
		if (auto val = std::get_if<T>(&m_Value))
			return *val;
		else
			throw std::runtime_error("Unsupported type requested for ReadValue.");
	}

private:
	const ValueType m_Value;
};

#endif //!ROLL_A_BALL_INCLUDE_INPUTACTIONCALLBACKCONTEXT_H_