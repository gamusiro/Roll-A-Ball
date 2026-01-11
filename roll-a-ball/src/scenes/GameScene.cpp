#include "scenes/GameScene.h"

#include "FontManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "TimeManager.h"

bool GameScene::Init()
{
    LOG_CORE_INFO("GameScene::Init");

    // Add event
    AddEventListener<WindowResizeEvent, GameScene, &GameScene::ResizeEvent>(*this);

    // Load shaders
    ShaderManager& sm = ShaderManager::Instance();
    sm.LoadShader(RENDERER_SHADER_DEFAULT, "default.vert", "default.frag");
    sm.LoadShader(RENDERER_SHADER_TEXT, "text.vert", "text.frag");
    sm.LoadShader(RENDERER_SHADER_PARTRICLE, "particle.vert", "particle.geom", "particle.frag");
    sm.LoadShader(RENDERER_SHADER_CANVAS, "canvas.vert", "canvas.frag");
    sm.LoadShader(COMPUTE_SHADER_PARTICLE, "particle.comp");

    // Load textures
    TextureManager& tm = TextureManager::Instance();
    tm.LoadTexture(TEXTURE_WHITE);
    tm.LoadTexture(TEXTURE_PARTICLE);

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

    tm.LoadTexture(TEXTURE_COLLECTABLE_ALBEDO);
    tm.LoadTexture(TEXTURE_COLLECTABLE_NORMAL);
    tm.LoadTexture(TEXTURE_COLLECTABLE_ROUGHNESS);
    tm.LoadTexture(TEXTURE_COLLECTABLE_DISPLACEMENT);

    tm.LoadTexture(TEXTURE_BURSTPARTICLE_COLOR_OVER_LIFETIME);
    
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

    // Particle
    {
        glm::vec3 position(0.0f, 5.0f, 0.0f);
        glm::vec3 euler(0.0f);
        glm::vec3 scale(1.0f);
        auto entity = Instantiate<BurstParticle>("Burst", position, euler, scale);
    }


    // Canvas
    {
        auto canvasEntity = Instantiate<Entity>("Canvas");
        auto& canvasRectTransform = canvasEntity->AddComponent<RectTransform>();
        canvasRectTransform.SetPosition(glm::vec2(0.0f));
        canvasRectTransform.SetSize(glm::vec2(DEFAULT_WIDTH, DEFAULT_HEIGHT));

        auto camEntity = FindEntity<MainCamera>("MainCamera");
        auto& canvas = canvasEntity->AddComponent<Canvas>();
        canvas.SetScreenSpaceOverlay();

        glm::vec2 resolution(1920.0f, 1080.0f);
        auto& canvasScaler = canvasEntity->AddComponent<CanvasScaler>();
        canvasScaler.SetScaleWithScreenSizeMatchWidthOrHeight(resolution, 0.0f, 100.0f);
        canvasScaler.SetScaleFactor(canvasRectTransform.GetSize());
    }

    // Text
    {
        auto canvasEntity = FindEntity<Entity>("Canvas");
        auto& canvasRectTransform = canvasEntity->GetComponent<RectTransform>();

        auto entity = Instantiate<Entity>("Counter Text");
        auto& rectTransform = entity->AddComponent<RectTransform>();
        rectTransform.SetParent(&canvasRectTransform);
        rectTransform.SetPosition(glm::vec2(100.0f, 25.0f));
        rectTransform.SetSize(glm::vec2(200.0f, 50.0f));

        auto counterEntt = FindEntity<Entity>("Counter");
        CollectableCounter& cc = counterEntt->GetComponent<CollectableCounter>();
        cc.SetValue(CollectableNum);

        std::string text = u8"残り" + std::to_string(cc.GetValue()) + u8"個";
        std::u32string output;

        utf8::utf8to32(text.begin(), text.end(), std::back_inserter(output));
        FontPtr font = FontManager::Instance().GetFont(FONT_NOTOSANS_JP);
        entity->AddComponent<Text>(output, font);

        entity->AddComponent<CanvasRenderer>();
    }

    return true;
}

void GameScene::Update()
{
    {// Update PlayerInput
        auto v = View<PlayerInput>();
        for (auto entity : v)
            v.get<PlayerInput>(entity).Update();
    }

    for(auto& pair : m_Entities)
        pair.second->Update();

    {// Update Particle
        auto v = View<ParticleSystem>();
        for (auto entity : v)
            v.get<ParticleSystem>(entity).Update();
    }

    // Get entity that has a CollectableCounter component
    auto counterEntity = FindEntity<Entity>("Counter");
    CollectableCounter& cc = counterEntity->GetComponent<CollectableCounter>();

    {// Collect all the collectable objects
        if (cc.GetValue() <= 0)
        {
            auto burstEntity = FindEntity<BurstParticle>("Burst");
            burstEntity->Burst();
        }
    }

    {// Update text
        std::string input = u8"残り" + std::to_string(cc.GetValue()) + u8"個";
        std::u32string output;

        utf8::utf8to32(input.begin(), input.end(), std::back_inserter(output));

        auto textEntt = FindEntity<Entity>("Counter Text");
        textEntt->GetComponent<Text>().SetText(output);
    }
}

void GameScene::Render() const
{
    // projection matrix
    auto camera = FindEntity<MainCamera>("MainCamera");
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = camera->GetComponent<PerspectiveCamera>().GetProjectionMatrix();

    glm::vec3 lightPositions[] = {
        glm::vec3( 10.0f, 5.0f,  10.0f),
        glm::vec3(-10.0f, 5.0f,  10.0f),
        glm::vec3( 10.0f, 5.0f, -10.0f),
        glm::vec3(-10.0f, 5.0f, -10.0f),
    };
    glm::vec3 lightColors[] = {
        glm::vec3(350.0f,   0.0f,   0.0f),
        glm::vec3(  0.0f,   0.0f, 350.0f),
        glm::vec3(  0.0f, 350.0f,   0.0f),
        glm::vec3(150.0f, 150.0f, 150.0f),
    };

    auto v = View<Transform, Material, MeshRenderer>();
    for(auto entity : v)
    {
        const Transform& transform = v.get<Transform>(entity);
        const Material& material = v.get<Material>(entity);
        const MeshRenderer& renderer = v.get<MeshRenderer>(entity);

        ShaderPtr shader = material.GetShader();
        shader->Bind();
        shader->Set("u_Albedo", material.GetAlbedo());
        shader->Set("u_Model", transform.GetWorldMatrix());
        shader->Set("u_View", view);
        shader->Set("u_Projection", projection);
        shader->Set("u_CamPos", camera->GetComponent<Transform>().GetPosition());
        shader->Set("u_AlbedoTexture", 0);
        shader->Set("u_NormalTexture", 1);
        shader->Set("u_RoughnessTexture", 2);
        shader->Set("u_MetalnessTexture", 3);
        shader->Set("u_DisplacementTexture", 4);

        for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
        {
            glm::vec3 dir = glm::normalize(lightPositions[i]);
            lightPositions[i] += dir * TimeManager::Instance().GetDeltaTime();
            shader->Set("u_LightPositions[" + std::to_string(i) + "]", lightPositions[i]);
            shader->Set("u_LightColors[" + std::to_string(i) + "]", lightColors[i]);
        }

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
        shader->Unbind();
    }

    {// Particle rendering
        auto v = View<Transform, Material, ParticleSystem, ParticleRenderer>();
        for(auto entity : v)
        {
            const Transform& transform = v.get<Transform>(entity);
            const Material& material = v.get<Material>(entity);
            const ParticleSystem& particle = v.get<ParticleSystem>(entity);
            const ParticleRenderer& renderer = v.get<ParticleRenderer>(entity);

            ShaderPtr shader = material.GetShader();
            shader->Bind();
            shader->Set("u_Model", transform.GetWorldMatrix());
            shader->Set("u_View", view);
            shader->Set("u_Projection", projection);
            shader->Set("u_Particle", 0);
            shader->Set("u_ColorOverLifeGradient", 1);

            glActiveTexture(GL_TEXTURE0);
            TextureManager::Instance().GetTexture(TEXTURE_PARTICLE)->Bind();

            glActiveTexture(GL_TEXTURE1);
            TextureManager::Instance().GetTexture(particle.GetColorOverLifetime())->Bind();

            renderer.Render(particle);
            shader->Unbind();
        }
    }

    {// UI rendering
        auto canvasEntity = FindEntity<Entity>("Canvas");
        auto& canvas = canvasEntity->GetComponent<Canvas>();
        auto& canvasScaler = canvasEntity->GetComponent<CanvasScaler>();
        auto& canvasRectTransform = canvasEntity->GetComponent<RectTransform>();

        float scaleFactor = canvasScaler.GetScaleFactor();
        glm::mat4 projection = canvas.GetProjection(canvasRectTransform);

        auto v = View<RectTransform, Text, CanvasRenderer>();
        for(auto entity : v)
        {
            const RectTransform& rectTransform = v.get<RectTransform>(entity);
            const Text& text = v.get<Text>(entity);
            const CanvasRenderer& renderer = v.get<CanvasRenderer>(entity);

            renderer.Render(projection, rectTransform, text);
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

    auto canvasEntity = FindEntity<Entity>("Canvas");
    auto& canvasScaler = canvasEntity->GetComponent<CanvasScaler>();
    canvasScaler.SetScaleFactor(glm::vec2(width, height));
    
    auto& canvasRectTransform = canvasEntity->GetComponent<RectTransform>();
    canvasRectTransform.SetSize(glm::vec2(width, height));
    canvasRectTransform.SetScale(glm::vec3(canvasScaler.GetScaleFactor()));
}
