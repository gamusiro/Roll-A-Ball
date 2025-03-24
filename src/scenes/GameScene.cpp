#include "scenes/GameScene.h"

bool GameScene::Init()
{
    LOG_CORE_INFO("GameScene::Init");
    
    // Player
    m_Player = Instantiate<Player>();
    
    // Camera
    m_MainCamera = Instantiate<MainCamera>();

    return true;
}

void GameScene::Update()
{
    if(!m_StartUpEntities.empty())
    {
        for(auto entity : m_StartUpEntities)
            entity->Start();
        m_StartUpEntities.clear();
    }

    auto view = View<Transform, RigidBody>();
    for(auto entity : view)
    {
        Transform& transform = view.get<Transform>(entity);
        RigidBody& rigidBody = view.get<RigidBody>(entity);
        transform.SetPosition(rigidBody.GetPosition());
    }

    m_Player->Update();
}

void GameScene::Render() const
{
    // projection matrix
    glm::mat4 view = m_MainCamera->GetViewMatrix();
    glm::mat4 projection = m_MainCamera->GetComponent<PerspectiveCamera>().GetProjectionMatrix();

    auto v = View<Transform, Shader, MeshRenderer>();
    for(auto entity : v)
    {
        const Transform& transform = v.get<Transform>(entity);
        const Shader& shader = v.get<Shader>(entity);
        const MeshRenderer& renderer = v.get<MeshRenderer>(entity);

        shader.Bind();
        shader.Set("u_Transform", transform.GetWorldMatrix());
        shader.Set("u_ViewProjection", projection * m_MainCamera->GetViewMatrix());

        renderer.Render();
    }
}

void GameScene::Term()
{
    LOG_CORE_INFO("GameScene::Term");
    m_StartUpEntities.clear();
}