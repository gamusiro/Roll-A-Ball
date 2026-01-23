#include "scenes/TitleScene.h"

#include "SceneManager.h"
#include "FontManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

bool TitleScene::Init()
{
    LOG_CORE_INFO("TitleScene::Init");

    // Add event
    AddEventListener<WindowResizeEvent, TitleScene, &TitleScene::ResizeEvent>(*this);

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

    {// Canvas
        auto canvasEntity = Instantiate<Entity>("Canvas");
        auto& canvasRectTransform = canvasEntity->AddComponent<RectTransform>();
        canvasRectTransform.SetPosition(glm::vec2(0.0f));
        canvasRectTransform.SetSize(glm::vec2(DEFAULT_WIDTH, DEFAULT_HEIGHT));

        auto& canvas = canvasEntity->AddComponent<Canvas>();
        canvas.SetScreenSpaceOverlay();

        glm::vec2 resolution(1920.0f, 1080.0f);
        auto& canvasScaler = canvasEntity->AddComponent<CanvasScaler>();
        canvasScaler.SetScaleWithScreenSizeMatchWidthOrHeight(resolution, 0.0f, 100.0f);
        canvasScaler.SetScaleFactor(canvasRectTransform.GetSize());
    }

    {// Button Entity
        auto canvasEntity = FindEntity<Entity>("Canvas");
        auto& canvasRectTransform = canvasEntity->GetComponent<RectTransform>();

        auto buttonEntity = Instantiate<Entity>("Button");
        auto& buttonRectTransform = buttonEntity->AddComponent<RectTransform>();
        buttonRectTransform.SetPosition(glm::vec2(960.0f, 540.0f));
        buttonRectTransform.SetSize(glm::vec2(250.f, 100.f));
        buttonRectTransform.SetParent(&canvasRectTransform);

        buttonEntity->AddComponent<CanvasRenderer>();

        auto& buttonImage = buttonEntity->AddComponent<Image>();
        buttonImage.SetSourceImage(TEXTURE_WHITE);
        buttonImage.SetColor(glm::vec4(1.0f));

        auto& buttonButton = buttonEntity->AddComponent<Button>();
        buttonButton.SetStateNormal();
        buttonButton.SetHighlightedColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        buttonButton.AddOnClick([&]() { OnClick(); });

        auto textEntity = Instantiate<Entity>("Text");
        auto& textRectTransform = textEntity->AddComponent<RectTransform>();
        textRectTransform.SetParent(&buttonRectTransform);
        textRectTransform.SetPosition(glm::vec2(0.0f));
        textRectTransform.SetSize(buttonRectTransform.GetSize());

        textEntity->AddComponent<CanvasRenderer>();

        std::string text = u8"Start";
        std::u32string output;
        utf8::utf8to32(text.begin(), text.end(), std::back_inserter(output));
        
        FontPtr font = FontManager::Instance().GetFont(FONT_NOTOSANS_JP);
        auto& textText = textEntity->AddComponent<Text>(output, font);
        textText.SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    }
    return true;
}

void TitleScene::Update()
{

}

void TitleScene::Render() const
{
    {// UI rendering
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        auto canvasEntity = FindEntity<Entity>("Canvas");
        auto& canvas = canvasEntity->GetComponent<Canvas>();
        auto& canvasScaler = canvasEntity->GetComponent<CanvasScaler>();
        auto& canvasRectTransform = canvasEntity->GetComponent<RectTransform>();

        float scaleFactor = canvasScaler.GetScaleFactor();
        glm::mat4 projection = canvas.GetProjection(canvasRectTransform);
        
        {
            auto v = View<RectTransform, Image, CanvasRenderer>();
            for (auto entity : v)
            {
                const RectTransform& rectTransform = v.get<RectTransform>(entity);
                const Image& image = v.get<Image>(entity);
                const CanvasRenderer& renderer = v.get<CanvasRenderer>(entity);

                renderer.Render(projection, rectTransform, image);
            }
        }

        {
            auto v = View<RectTransform, Text, CanvasRenderer>();
            for (auto entity : v)
            {
                const RectTransform& rectTransform = v.get<RectTransform>(entity);
                const Text& text = v.get<Text>(entity);
                const CanvasRenderer& renderer = v.get<CanvasRenderer>(entity);

                renderer.Render(projection, rectTransform, text);
            }
        }
    }
}

void TitleScene::Term()
{
    LOG_CORE_INFO("TitleScene::Term");
}

void TitleScene::ResizeEvent(const WindowResizeEvent& e)
{
    LOG_CORE_INFO("TitleScene::ResizeEvent");

    float width = static_cast<float>(e.GetWidth());
    float height = static_cast<float>(e.GetHeight());

    auto canvasEntity = FindEntity<Entity>("Canvas");
    auto& canvasScaler = canvasEntity->GetComponent<CanvasScaler>();
    canvasScaler.SetScaleFactor(glm::vec2(width, height));

    auto& canvasRectTransform = canvasEntity->GetComponent<RectTransform>();
    canvasRectTransform.SetSize(glm::vec2(width, height));
    canvasRectTransform.SetScale(glm::vec3(canvasScaler.GetScaleFactor()));
}


void TitleScene::OnClick()
{
    SceneManager::Instance().LoadScene("Game");
}