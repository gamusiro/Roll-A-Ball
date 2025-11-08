#ifndef ROLL_A_BALL_INCLUDE_PLAYERINPUT_H_
#define ROLL_A_BALL_INCLUDE_PLAYERINPUT_H_
#include "Config.h"

#include "Component.h"
#include "InputAction.h"

class PlayerInput : public Component
{
public:
	PlayerInput(std::shared_ptr<Entity> entity);
	void Update();
	void AddAction(const InputAction& action);

private:
	std::vector<InputAction> m_Actions;
};

#endif //!ROLL_A_BALL_INCLUDE_PLAYERINPUT_H_