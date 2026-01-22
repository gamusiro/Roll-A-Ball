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
