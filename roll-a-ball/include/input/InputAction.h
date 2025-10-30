#pragma once
#include <memory>

#include "IComposite.h"


class InputAction 
{
public:
    using Callback = std::function<void(const CallbackContext&)>;

    InputAction(std::shared_ptr<IComposite> comp, Callback cb)
        : composite(comp), callback(cb) {}

    void Process(const InputContext& context) 
    {
        if (composite && callback)
            if(composite->IsFire(context))
                callback(composite->Evaluate(context));
    }

private:
    std::shared_ptr<IComposite> composite;
    Callback callback;
};

