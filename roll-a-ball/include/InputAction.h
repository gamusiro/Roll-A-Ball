#ifndef ROLL_A_BALL_INCLUDE_INPUTACTION_H_
#define ROLL_A_BALL_INCLUDE_INPUTACTION_H_
#include "Config.h"

#include "InputContext.h"
#include "InputPath.h"
#include "InputComposite.h"
#include "InputActionCallbackContext.h"

class InputAction
{
public:
	using Callback = std::function<void(const InputActionCallbackContext& context)>;

public:
	InputAction(
		const std::string& actionName, 
		std::vector<PathType> bindings, 
		std::shared_ptr<InputComposite> composite,
		Callback func)
		:m_Name(actionName), m_Bindings(bindings), m_Composite(composite), m_Callback(func) {}

	void Process(InputContext& context);

private:
	std::string m_Name;
	std::shared_ptr<InputComposite> m_Composite;
	std::vector<PathType> m_Bindings;
	Callback m_Callback;
};

#endif //!ROLL_A_BALL_INCLUDE_INPUTACTION_H_