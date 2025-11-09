#ifndef ROLL_A_BALL_INCLUDE_ENTITIES_MAINCAMERA_H_
#define ROLL_A_BALL_INCLUDE_ENTITIES_MAINCAMERA_H_
#include "Config.h"

#include "Entity.h"

class MainCamera : public Entity
{
public:
    MainCamera(ScenePtr scene);
    void Awake() override;
    void Update() override;

public:
    inline glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }

private:
    glm::mat4 m_ViewMatrix;
    glm::vec3 m_Offset;
};

#endif //!ROLL_A_BALL_INCLUDE_ENTITIES_MAINCAMERA_H_