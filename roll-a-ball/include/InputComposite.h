#ifndef ROLL_A_BALL_INCLUDE_INPUTCOMPOSITE_H_
#define ROLL_A_BALL_INCLUDE_INPUTCOMPOSITE_H_
#include "Config.h"

#include "InputContext.h"
#include "InputPath.h"
#include "InputActionCallbackContext.h"

class InputComposite
{
public:
	virtual ~InputComposite() {}
	virtual bool IsFire(InputContext& context) = 0;
	virtual const InputActionCallbackContext Evaluate(InputContext& context) = 0;
};

#endif //!ROLL_A_BALL_INCLUDE_INPUTCOMPOSITE_H_