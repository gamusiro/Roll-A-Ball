#pragma once
#include <unordered_map>

class InputManager
{
public:
	static InputManager& Instance()
	{
		static InputManager instance;
		return instance;
	}

	void SetKey(int key, bool pressed)
	{
		m_keyStates[key] = pressed ? 1.0f : 0.0f;
	}

	float GetKey(int key) const
	{
		auto it = m_keyStates.find(key);
		return it != m_keyStates.end() ? it->second : 0.0f;
	}

private:
	std::unordered_map<int, float> m_keyStates;
};

