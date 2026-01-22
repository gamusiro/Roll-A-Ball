#ifndef ROLL_A_BALL_INCLUDE_SCENES_TITLESCENE_H_
#define ROLL_A_BALL_INCLUDE_SCENES_TITLESCENE_H_
#include "Config.h"
#include "Scene.h"

#include "ApplicationEvent.h"

// entities


class TitleScene : public Scene
{
public:
    bool Init() override;
    void Update() override;
    void Render() const override;
    void Term() override;

    void ResizeEvent(const WindowResizeEvent& e);

private:
    void OnCommitKey(const InputActionCallbackContext& context);
};


#endif //!ROLL_A_BALL_INCLUDE_SCENES_TITLESCENE_H_