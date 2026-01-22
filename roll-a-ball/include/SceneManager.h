#ifndef ROLL_A_BALL_INCLUDE_SCENEMANAGER_H_
#define ROLL_A_BALL_INCLUDE_SCENEMANAGER_H_
#include "Config.h"
#include "Scene.h"

class SceneManager
{
public:
    using SceneFactory = std::function<ScenePtr()>;

public:
    static SceneManager& Instance();
    void AddScene(const std::string& sceneName, SceneFactory factory);
    void LoadScene(size_t index);
    void LoadScene(const std::string& sceneName);
    inline bool Empty() const { return m_CurScene == nullptr; }

private:
    void update();
    void render();
    void term();

private:
    SceneManager() = default;
    ~SceneManager() = default;
    SceneManager(const SceneManager&) = delete;
    SceneManager operator= (const SceneManager&) = delete;

private:
    std::vector<std::string> m_SceneNames;
    std::unordered_map<std::string, SceneFactory> m_Scenes;

private:
    ScenePtr m_CurScene;
    friend class Application;
};

#endif //!ROLL_A_BALL_INCLUDE_SCENEMANAGER_H_