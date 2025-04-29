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
};


#endif //!ROLL_A_BALL_INCLUDE_SCENES_GAMESCENE_H_