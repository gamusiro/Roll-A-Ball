#include "PlayerInput.h"

#include "InputManager.h"
#include "InputContext.h"
#include "InputAction.h"


PlayerInput::PlayerInput(std::shared_ptr<Entity> entity)
	:Component(entity)
{
}

void PlayerInput::Update()
{
	InputManager& im = InputManager::Instance();
	InputContext context(im);
	for (auto& action : m_Actions)
		action.Process(context);
}

void PlayerInput::AddAction(const InputAction& action)
{
	m_Actions.push_back(action);
}
