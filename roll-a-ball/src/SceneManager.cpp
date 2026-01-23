#include "SceneManager.h"

#include "Scene.h"
#include "Physics.h"
#include "MeshManager.h"

SceneManager& SceneManager::Instance()
{
    static SceneManager instance;
    return instance;
}

void SceneManager::AddScene(const std::string& sceneName, SceneFactory factory)
{
    m_SceneNames.push_back(sceneName);
    m_Scenes[sceneName] = factory;
}

void SceneManager::LoadScene(size_t index)
{
    LoadScene(m_SceneNames[index]);
}

void SceneManager::LoadScene(const std::string& sceneName)
{
    if(!Empty())
        m_CurScene->Term();
    
    MeshManager::Instance().Clear();
    
    m_CurScene = m_Scenes[sceneName]();
    m_CurScene->Init();
}

void SceneManager::update()
{
    // Physics
    entt::registry& registry = m_CurScene->m_Registry;
    Physics::Instance().update(registry);

    // Entity call start
    m_CurScene->Update();

    // Input UI
    glm::vec2 cursorPos = InputManager::Instance().GetMouse();
    auto v = registry.view<RectTransform, Button, Image>();
    for (auto& entity : v)
    {
        auto& rc = v.get<RectTransform>(entity);
        auto& btn = v.get<Button>(entity);
        auto& img = v.get<Image>(entity);

        glm::vec2 pos = rc.GetPosition();
        glm::vec2 size = rc.GetSize() * 0.5f;

        bool hit =
            cursorPos.x >= pos.x - size.x &&
            cursorPos.x <= pos.x + size.x &&
            cursorPos.y >= pos.y - size.y &&
            cursorPos.y <= pos.y + size.y;

        if (hit)
        {
            if (InputManager::Instance().GetMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
                btn.SetStatePressed();
            else
                btn.SetStateHover();
        }
        else
        {
            btn.SetStateNormal();
        }

        img.SetColor(btn.GetColor());
    }
}

void SceneManager::render()
{
    m_CurScene->Render();
}

void SceneManager::term()
{
    if(!Empty())
        m_CurScene->Term();
}
