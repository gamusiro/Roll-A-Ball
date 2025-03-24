#ifndef ROLL_A_BALL_INCLUDE_SCENES_GAMESCENE_H_
#define ROLL_A_BALL_INCLUDE_SCENES_GAMESCENE_H_
#include "Config.h"
#include "Scene.h"

// entities
#include "entities/Player.h"
#include "entities/MainCamera.h"

class GameScene : public Scene
{
public:
    bool Init() override;
    void Update() override;
    void Render() const override;
    void Term() override;

private:
    std::unique_ptr<Player> m_Player;
    std::unique_ptr<MainCamera> m_MainCamera;
};


#endif //!ROLL_A_BALL_INCLUDE_SCENES_GAMESCENE_H_