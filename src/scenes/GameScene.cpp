#include "scenes/GameScene.h"

bool GameScene::Init()
{
    LOG_CORE_INFO("GameScene::Init");
    
    // Player
    {
        glm::vec3 position(0.0f, 5.0f, 0.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(1.0f);
        m_Player = Instantiate<Player>(position, euler, scale);
    }
    
    // Camera
    {
        glm::vec3 position(0.0f, 5.0f, 15.0f);
        glm::quat rotation = glm::quat(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::vec3 scale(1.0f);
        m_MainCamera = Instantiate<MainCamera>(position, rotation, scale);
    }
    
    // Ground
    {
        glm::vec3 position(0.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(5.0f, 1.0f, 5.0f);
        m_Ground = Instantiate<Ground>(position, euler, scale);
    }

    // Walls North
    {
        glm::vec3 position(0.0f, 0.5f, 5.5f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(5.0f, 1.0f, 0.5f);
        m_Walls.push_back(Instantiate<Wall>(position, euler, scale));
    }

    // Walls South
    {
        glm::vec3 position(0.0f, 0.5f, -5.5f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(5.0f, 1.0f, 0.5f);
        m_Walls.push_back(Instantiate<Wall>(position, euler, scale));
    }

    // Walls East
    {
        glm::vec3 position(5.5f, 0.5f, 0.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(0.5f, 1.0f, 5.0f);
        m_Walls.push_back(Instantiate<Wall>(position, euler, scale));
    }

    // Walls West
    {
        glm::vec3 position(-5.5f, 0.5f, 0.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(0.5f, 1.0f, 5.0f);
        m_Walls.push_back(Instantiate<Wall>(position, euler, scale));
    }

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