#include "Application.h"
#include "SceneManager.h"

#include "scenes/TitleScene.h"
#include "scenes/GameScene.h"
#include "scenes/ResultScene.h"

int main()
{
    SceneManager& sm = SceneManager::Instance();
    sm.AddScene("Title", []() { return std::make_shared<TitleScene>();});
    sm.AddScene("Game", []() { return std::make_shared<GameScene>();});
    sm.AddScene("Result", []() { return std::make_shared<ResultScene>();});

    Application app;
    app.Run();
    return 0;
}