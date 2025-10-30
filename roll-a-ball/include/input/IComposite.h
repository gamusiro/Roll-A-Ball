#pragma once
#include <vector>

#include "InputContext.h"
#include "CallbackContext.h"

class IComposite 
{
public:
    virtual ~IComposite() = default;
    virtual CallbackContext Evaluate(const InputContext& context) = 0;
    virtual bool IsFire(const InputContext& context) = 0;
};

