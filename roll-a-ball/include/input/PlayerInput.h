#pragma once
#include <functional>
#include <string>

#include "InputManager.h"
#include "IComposite.h"
#include "InputAction.h"

class PlayerInput 
{
public:
    explicit PlayerInput() : context(InputManager::Instance()) {}

    void AddAction(std::string name, std::shared_ptr<IComposite> composite, std::function<void(const CallbackContext&)> callback) 
    {
        actions[name] = std::make_shared<InputAction>(composite, callback);
    }

    void Update() 
    {
        for (auto& [_, action] : actions)
            action->Process(context);
    }

private:
    InputContext context;
    std::unordered_map<std::string, std::shared_ptr<InputAction>> actions;
};

