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
        auto player = Instantiate<Player>("Player", position, euler, scale);
        AddEventListener<KeyEventPressed, Player, &Player::KeyPressed>(*player);
    }
    
    // Camera
    {
        glm::vec3 position(0.0f, 7.0f, 15.0f);
        glm::vec3 euler = glm::vec3(glm::radians(-20.0f), 0.0f, 0.0f);
        //glm::vec3 position(0.0f, 25.0f, 0.0f);
        //glm::vec3 euler = glm::vec3(glm::radians(-89.0f), 0.0f, 0.0f);
        glm::vec3 scale(1.0f);
        Instantiate<MainCamera>("MainCamera", position, euler, scale);
    }
    
    // Ground
    {
        glm::vec3 position(0.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(2.0f, 1.0f, 2.0f);
        Instantiate<Ground>("Ground", position, euler, scale);
    }

    // Wall 01
    {
        glm::vec3 position(-10.0f, 0.5f, 0.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(0.5f, 1.0f, 10.5f);
        Instantiate<Wall>("Wall_01", position, euler, scale);
    }

    // Wall 02
    {
        glm::vec3 position(10.0f, 0.5f, 0.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(0.5f, 1.0f, 10.5f);
        Instantiate<Wall>("Wall_02", position, euler, scale);
    }

    // Wall 03
    {
        glm::vec3 position(0.0f, 0.5f, -10.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(10.5f, 1.0f, 0.5f);
        Instantiate<Wall>("Wall_03", position, euler, scale);
    }

    // wall 04
    {
        glm::vec3 position(0.0f, 0.5f, 10.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(10.5f, 1.0f, 0.5f);
        Instantiate<Wall>("Wall_04", position, euler, scale);
    }

    // Collectables
    const float deg = 360.0f / 12.0f;
    for(int i = 0; i < 12; ++i) {
        glm::vec3 position(cosf(glm::radians(deg * float(i))) * 5.0f, 1.0f, sinf(glm::radians(deg * float(i))) * 5.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(0.5f);

        std::stringstream ss;
        ss << "Collectable_" << std::setw(2) << std::setfill('0') << i;
        Instantiate<Collectable>(ss.str(), position, euler, scale);
    }

    return true;
}

void GameScene::Update()
{
    for(auto& pair : m_Entities)
        pair.second->Update();
}

void GameScene::Render() const
{
    // projection matrix
    auto camera = FindEntity<MainCamera>("MainCamera");
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = camera->GetComponent<PerspectiveCamera>().GetProjectionMatrix();

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
        shader->Set("u_ViewProjection", projection * view);

        renderer.Render();
    }
}

void GameScene::Term()
{
    LOG_CORE_INFO("GameScene::Term");
}