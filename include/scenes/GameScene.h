#ifndef ROLL_A_BALL_INCLUDE_SCENES_GAMESCENE_H_
#define ROLL_A_BALL_INCLUDE_SCENES_GAMESCENE_H_
#include "Config.h"
#include "Scene.h"

// entities
#include "entities/Player.h"
#include "entities/MainCamera.h"
#include "entities/Ground.h"
#include "entities/Wall.h"
#include "entities/Collectable.h"

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
    std::unique_ptr<Ground> m_Ground;
    std::unique_ptr<Collectable> m_Collectables;
    std::vector<std::unique_ptr<Wall>> m_Walls;
};


#endif //!ROLL_A_BALL_INCLUDE_SCENES_GAMESCENE_H_