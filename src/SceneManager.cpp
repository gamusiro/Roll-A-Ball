#include "SceneManager.h"

#include "Scene.h"

SceneManager& SceneManager::Instance()
{
    static SceneManager instance;
    return instance;
}

void SceneManager::LoadScene(std::shared_ptr<Scene> scene)
{
    if(!Empty())
        m_CurScene->Term();
    
    m_CurScene = scene;
    m_CurScene->Init();
}

void SceneManager::update()
{
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
