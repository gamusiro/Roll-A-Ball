#include "scenes/ResultScene.h"

#include "SceneManager.h"

bool ResultScene::Init()
{
    LOG_CORE_INFO("ResultScene::Init");

    // Add event
    AddEventListener<WindowResizeEvent, ResultScene, &ResultScene::ResizeEvent>(*this);

    // Input control
    {
        InputAction commitAction(
            "Commit",
            { InputPath::Keyboard::ENTER },
            std::make_shared<ButtonComposite>(InputPath::Keyboard::ENTER),
            std::bind(&ResultScene::OnCommitKey, this, std::placeholders::_1));

        auto entity = Instantiate<Entity>("Input");
        PlayerInput& playerInput = entity->AddComponent<PlayerInput>();
        playerInput.AddAction(commitAction);
    }

    return true;
}

void ResultScene::Update()
{
    {// Update PlayerInput
        auto v = View<PlayerInput>();
        for (auto entity : v)
            v.get<PlayerInput>(entity).Update();
    }
}

void ResultScene::Render() const
{
    
}

void ResultScene::Term()
{
    LOG_CORE_INFO("ResultScene::Term");
}

void ResultScene::ResizeEvent(const WindowResizeEvent& e)
{
    LOG_CORE_INFO("ResultScene::ResizeEvent");
}

void ResultScene::OnCommitKey(const InputActionCallbackContext& context)
{
    SceneManager::Instance().LoadScene("Title");
}
