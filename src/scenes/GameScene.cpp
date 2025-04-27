#include "scenes/GameScene.h"
#include "ShaderManager.h"

bool GameScene::Init()
{
    LOG_CORE_INFO("GameScene::Init");

    // Load shaders
    ShaderManager& sm = ShaderManager::Instance();
    sm.LoadShader(SHADER_DEFAULT_3D, "default.vert", "default.frag");
    
    // Player
    {
        glm::vec3 position(0.0f, 0.5f, 0.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(1.0f);
        m_Player = Instantiate<Player>(position, euler, scale);
        AddEventListener<KeyEventPressed, Player, &Player::KeyPressed>(*m_Player.get());
    }
    
    // Camera
    {
        glm::vec3 position(0.0f, 7.0f, 15.0f);
        glm::vec3 euler = glm::vec3(glm::radians(-20.0f), 0.0f, 0.0f);
        //glm::vec3 position(0.0f, 25.0f, 0.0f);
        //glm::vec3 euler = glm::vec3(glm::radians(-89.0f), 0.0f, 0.0f);
        glm::vec3 scale(1.0f);
        m_MainCamera = Instantiate<MainCamera>(position, euler, scale);

        Transform& player = m_Player->GetComponent<Transform>();
        Transform& camera = m_MainCamera->GetComponent<Transform>();
        camera.SetParent(&player);
    }
    
    // Ground
    {
        glm::vec3 position(0.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(2.0f, 1.0f, 2.0f);
        m_Ground = Instantiate<Ground>(position, euler, scale);
    }

    // Wall 01
    {
        glm::vec3 position(-10.0f, 0.5f, 0.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(0.5f, 1.0f, 20.5f);
        m_Walls.push_back(Instantiate<Wall>(position, euler, scale));
    }

    // Wall 02
    {
        glm::vec3 position(10.0f, 0.5f, 0.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(0.5f, 1.0f, 20.5f);
        m_Walls.push_back(Instantiate<Wall>(position, euler, scale));
    }

    // Wall 03
    {
        glm::vec3 position(0.0f, 0.5f, -10.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(20.5f, 1.0f, 0.5f);
        m_Walls.push_back(Instantiate<Wall>(position, euler, scale));
    }

    // wall 04
    {
        glm::vec3 position(0.0f, 0.5f, 10.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(20.5f, 1.0f, 0.5f);
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
    m_MainCamera->Update();
}

void GameScene::Render() const
{
    // projection matrix
    glm::mat4 view = m_MainCamera->GetViewMatrix();
    glm::mat4 projection = m_MainCamera->GetComponent<PerspectiveCamera>().GetProjectionMatrix();

    auto v = View<Transform, Material, MeshRenderer>();
    for(auto entity : v)
    {
        const Transform& transform = v.get<Transform>(entity);
        const Material& material = v.get<Material>(entity);
        const MeshRenderer& renderer = v.get<MeshRenderer>(entity);

        ShaderPtr shader = material.GetShader();
        shader->Bind();
        shader->Set("u_Albedo", material.GetAlbedo());
        shader->Set("u_Transform", transform.GetWorldMatrix());
        shader->Set("u_ViewProjection", projection * m_MainCamera->GetViewMatrix());

        renderer.Render();
    }
}

void GameScene::Term()
{
    LOG_CORE_INFO("GameScene::Term");
    m_StartUpEntities.clear();
}