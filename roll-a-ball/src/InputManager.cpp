#include "InputManager.h"

InputManager& InputManager::Instance()
{
	static InputManager instance;
	return instance;
}

bool InputManager::GetKey(int code)
{
	return m_Keyboard.pressed[code];
}

bool InputManager::GetMouse(int code)
{
	return m_Mouse.pressed[code];
}

glm::vec2 InputManager::GetMouse()
{
	return m_Mouse.deltaPoint;
}

void InputManager::update()
{
	// Keyboard
	for (auto& [i, val] : m_Keyboard.pressed)
		m_Keyboard.trigger[i] = (val && !m_Keyboard.previous[i]);

	for (auto& [i, val] : m_Keyboard.previous)
		m_Keyboard.released[i] = (val && !m_Keyboard.pressed[i]);

	m_Keyboard.previous = m_Keyboard.pressed;

	// Mouse
	for (auto& [i, val] : m_Mouse.pressed)
		m_Mouse.trigger[i] = (val && !m_Mouse.previous[i]);

	for (auto& [i, val] : m_Mouse.previous)
		m_Mouse.released[i] = (val && !m_Mouse.pressed[i]);

	m_Mouse.previous = m_Mouse.pressed;
}

void InputManager::reset()
{
	m_Mouse.deltaPoint = glm::vec2(0.0f);
}

void InputManager::setKey(int code, bool press)
{
	m_Keyboard.pressed[code] = press;
}

void InputManager::setMouse(int code, bool press)
{
	m_Mouse.pressed[code] = press;
}

void InputManager::setMouse(float x, float y)
{
	glm::vec2 prevPoint = m_Mouse.currPoint;
	m_Mouse.currPoint = glm::vec2(x, y);
	m_Mouse.deltaPoint += prevPoint - m_Mouse.currPoint;
}
