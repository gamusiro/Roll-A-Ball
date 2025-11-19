#include "scenes/GameScene.h"

#include "FontManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

bool GameScene::Init()
{
    LOG_CORE_INFO("GameScene::Init");

    // Add event
    AddEventListener<WindowResizeEvent, GameScene, &GameScene::ResizeEvent>(*this);

    // Load shaders
    ShaderManager& sm = ShaderManager::Instance();
    sm.LoadShader(SHADER_DEFAULT, "default.vert", "default.frag");
    sm.LoadShader(SHADER_UI, "ui.vert", "ui.frag");

    // Load textures
    TextureManager& tm = TextureManager::Instance();
    tm.LoadTexture(TEXTURE_WHITE);

    tm.LoadTexture(TEXTURE_PLAYER_ALBEDO);
    tm.LoadTexture(TEXTURE_PLAYER_NORMAL);
    tm.LoadTexture(TEXTURE_PLAYER_METALNESS);
    tm.LoadTexture(TEXTURE_PLAYER_ROUGHNESS);
    tm.LoadTexture(TEXTURE_PLAYER_DISPLACEMENT);

    tm.LoadTexture(TEXTURE_GROUND_ALBEDO);
    tm.LoadTexture(TEXTURE_GROUND_NORMAL);
    tm.LoadTexture(TEXTURE_GROUND_ROUGHNESS);
    tm.LoadTexture(TEXTURE_GROUND_DISPLACEMENT);

    tm.LoadTexture(TEXTURE_WALL_ALBEDO);
    tm.LoadTexture(TEXTURE_WALL_NORMAL);
    tm.LoadTexture(TEXTURE_WALL_ROUGHNESS);
    tm.LoadTexture(TEXTURE_WALL_DISPLACEMENT);
    
    // Player
    {
        glm::vec3 position(0.0f, 0.5f, 0.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(1.0f);
        auto player = Instantiate<Player>("Player", position, euler, scale);
    }
    
    // Camera
    {
        glm::vec3 position(0.0f, 10.0f, 15.0f);
        glm::vec3 euler = glm::vec3(glm::radians(-30.0f), 0.0f, 0.0f);
        glm::vec3 scale(1.0f);
        auto camera = Instantiate<MainCamera>("MainCamera", position, euler, scale);
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
    const int CollectableNum = 12;
    const float deg = 360.0f / float(CollectableNum);
    for(int i = 0; i < CollectableNum; ++i) 
    {
        glm::vec3 position(cosf(glm::radians(deg * float(i))) * 5.0f, 1.0f, sinf(glm::radians(deg * float(i))) * 5.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(0.5f);

        std::stringstream ss;
        ss << "Collectable_" << std::setw(2) << std::setfill('0') << i;
        Instantiate<Collectable>(ss.str(), position, euler, scale);
    }

    // Collectable Counter
    {
        auto entity = Instantiate<Entity>("Counter");
        entity->AddComponent<CollectableCounter>(CollectableNum);
    }

    // UI
    {
        auto entity = Instantiate<Entity>("Counter Text");
        Material& material = entity->AddComponent<Material>();
        material.SetAlbedo(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        material.SetShader(ShaderManager::Instance().GetShader(SHADER_UI));

        auto counterEntt = FindEntity<Entity>("Counter");
        CollectableCounter& cc = counterEntt->GetComponent<CollectableCounter>();
        cc.SetValue(CollectableNum);

        std::string text = u8"残り" + std::to_string(cc.GetValue()) + u8"個";
        std::u32string output;

        utf8::utf8to32(text.begin(), text.end(), std::back_inserter(output));
        FontPtr font = FontManager::Instance().GetFont(FONT_NOTOSANS_JP);
        entity->AddComponent<Text>(output, font);

        entity->AddComponent<TextRenderer>();
    }

    return true;
}

void GameScene::Update()
{
    auto v = View<PlayerInput>();
    for (auto entity : v)
        v.get<PlayerInput>(entity).Update();

    for(auto& pair : m_Entities)
        pair.second->Update();

    {// Update text
        auto counterEntt = FindEntity<Entity>("Counter");
        CollectableCounter& cc = counterEntt->GetComponent<CollectableCounter>();

        std::string input = u8"残り" + std::to_string(cc.GetValue()) + u8"個";
        std::u32string output;

        utf8::utf8to32(input.begin(), input.end(), std::back_inserter(output));

        auto textEntt = FindEntity<Entity>("Counter Text");
        textEntt->GetComponent<Text>().SetText(output);
    }

}

void GameScene::Render() const
{
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
            shader->Set("u_CamPos", camera->GetComponent<Transform>().GetPosition());
            shader->Set("u_AlbedoTexture", 0);
            shader->Set("u_NormalTexture", 1);
            shader->Set("u_RoughnessTexture", 2);
            shader->Set("u_MetalnessTexture", 3);
            shader->Set("u_DisplacementTexture", 4);

            glActiveTexture(GL_TEXTURE0);
            material.GetAlbedoTexture()->Bind();

            glActiveTexture(GL_TEXTURE1);
            material.GetNormalTexture()->Bind();

            glActiveTexture(GL_TEXTURE2);
            material.GetRoughnessTexture()->Bind();

            glActiveTexture(GL_TEXTURE3);
            material.GetMetalnessTexture()->Bind();

            glActiveTexture(GL_TEXTURE4);
            material.GetDisplacementTexture()->Bind();

            renderer.Render();
        }
    }

    {// UI rendering
        auto v = View<Text, Material, TextRenderer>();
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(DEFAULT_WIDTH), 0.0f, static_cast<float>(DEFAULT_HEIGHT));

        for(auto entity : v)
        {
            const Text& text = v.get<Text>(entity);
            const Material& material = v.get<Material>(entity);
            const TextRenderer& renderer = v.get<TextRenderer>(entity);

            ShaderPtr shader = material.GetShader();
            shader->Bind();
            shader->Set("u_Albedo", material.GetAlbedo());
            shader->Set("u_Projection", projection);

            //renderer.Render(text);
        }
    } 
}

void GameScene::Term()
{
    LOG_CORE_INFO("GameScene::Term");
}

void GameScene::ResizeEvent(const WindowResizeEvent& e)
{
    LOG_CORE_INFO("GameScene::ResizeEvent");

    auto camera = FindEntity<MainCamera>("MainCamera");
    PerspectiveCamera& pers = camera->GetComponent<PerspectiveCamera>();
    
    float width = static_cast<float>(e.GetWidth());
    float height = static_cast<float>(e.GetHeight());
    pers.SetAspect(width, height);
}
