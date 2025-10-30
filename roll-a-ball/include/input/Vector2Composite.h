#pragma once
#include <glm/glm.hpp>

#include "IComposite.h"

class Vector2Composite : public IComposite
{
public:
    Vector2Composite(int up, int down, int left, int right)
        : upKey(up), downKey(down), leftKey(left), rightKey(right) {}

    CallbackContext Evaluate(const InputContext& context) override 
    {
        float x = context.ReadValue<float>(rightKey) - context.ReadValue<float>(leftKey);
        float y = context.ReadValue<float>(upKey) - context.ReadValue<float>(downKey);
        glm::vec2 result(x, y);
        if (glm::length(result) > 1.0f)
            result = glm::normalize(result);
        return CallbackContext(result);
    }

    bool IsFire(const InputContext& context) override
    {
        return (context.Pressed(upKey) || context.Pressed(downKey)
                || context.Pressed(leftKey) || context.Pressed(rightKey));
    }

private:
    int upKey, downKey, leftKey, rightKey;
};

