#pragma once
#include "InputManager.h"

class InputContext 
{
public:
    explicit InputContext(const InputManager& mgr) : manager(mgr) {}

    template<typename T>
    T ReadValue(int key) const 
    {
        if constexpr (std::is_same_v<T, float>)
            return manager.GetKey(key);
        else
            static_assert(sizeof(T) == 0, "Unsupported type for ReadValue");
    }

    bool Pressed(int key) const
    {
        return manager.GetKey(key) != 0.0f;
    }
private:
    const InputManager& manager;
};

