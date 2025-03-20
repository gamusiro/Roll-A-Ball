#ifndef ROLL_A_BALL_INCLUDE_SCENES_GAMESCENE_H_
#define ROLL_A_BALL_INCLUDE_SCENES_GAMESCENE_H_
#include "Config.h"
#include "Scene.h"

#include "entities/Player.h"

class GameScene : public Scene
{
public:
    bool Init() override;
    void Update() override;
    void Render() const override;
    void Term() override;

private:
    std::unique_ptr<Player> m_Player;
    //Entity m_Camera;
};


#endif //!ROLL_A_BALL_INCLUDE_SCENES_GAMESCENE_H_