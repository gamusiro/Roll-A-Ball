#include "SceneManager.h"

#include "Scene.h"
#include "Physics.h"
#include "MeshManager.h"

SceneManager& SceneManager::Instance()
{
    static SceneManager instance;
    return instance;
}

void SceneManager::LoadScene(std::shared_ptr<Scene> scene)
{
    if(!Empty())
        m_CurScene->Term();
    
    MeshManager::Instance().Clear();
    
    m_CurScene = scene;
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
