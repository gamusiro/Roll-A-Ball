#ifndef ROLL_A_BALL_INCLUDE_SCENEMANAGER_H_
#define ROLL_A_BALL_INCLUDE_SCENEMANAGER_H_
#include "Config.h"
#include "Scene.h"

class SceneManager
{
public:
    static SceneManager& Instance();

    void LoadScene(ScenePtr scene);
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
    ScenePtr m_CurScene;
    friend class Application;
};

#endif //!ROLL_A_BALL_INCLUDE_SCENEMANAGER_H_