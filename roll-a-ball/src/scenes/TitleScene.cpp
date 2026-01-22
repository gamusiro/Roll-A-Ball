#include "scenes/TitleScene.h"

#include "SceneManager.h"

bool TitleScene::Init()
{
    LOG_CORE_INFO("TitleScene::Init");

    // Add event
    AddEventListener<WindowResizeEvent, TitleScene, &TitleScene::ResizeEvent>(*this);

    // Input control
    {
        InputAction commitAction(
            "Commit",
            { InputPath::Keyboard::ENTER },
            std::make_shared<ButtonComposite>(InputPath::Keyboard::ENTER),
            std::bind(&TitleScene::OnCommitKey, this, std::placeholders::_1));

        auto entity = Instantiate<Entity>("Input");
        PlayerInput& playerInput = entity->AddComponent<PlayerInput>();
        playerInput.AddAction(commitAction);
    }

    

    return true;
}

void TitleScene::Update()
{
    {// Update PlayerInput
        auto v = View<PlayerInput>();
        for (auto entity : v)
            v.get<PlayerInput>(entity).Update();
    }
}

void TitleScene::Render() const
{
    
}

void TitleScene::Term()
{
    LOG_CORE_INFO("TitleScene::Term");
}

void TitleScene::ResizeEvent(const WindowResizeEvent& e)
{
    LOG_CORE_INFO("TitleScene::ResizeEvent");
}


void TitleScene::OnCommitKey(const InputActionCallbackContext& context)
{
    SceneManager::Instance().LoadScene("Game");
}