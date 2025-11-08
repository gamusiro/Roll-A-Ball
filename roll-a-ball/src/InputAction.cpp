#include "InputAction.h"

void InputAction::Process(InputContext& context)
{
	for (auto& bind : m_Bindings)
	{
		if (m_Composite->IsFire(context))
		{
			InputActionCallbackContext callbackContext = m_Composite->Evaluate(context);
			m_Callback(callbackContext);
			return;
		}
			
	}
}
