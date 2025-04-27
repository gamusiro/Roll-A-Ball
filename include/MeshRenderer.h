#ifndef ROLL_A_BALL_INCLUDE_MESHRENDERER_H_
#define ROLL_A_BALL_INCLUDE_MESHRENDERER_H_
#include "Config.h"

#include "Component.h"

class Mesh;
class MeshRenderer : public Component
{
public:
    MeshRenderer(const Entity* entity, const MeshPtr mesh);

public:
    void Render() const;

private:
    const MeshPtr m_Mesh;
};

#endif //!ROLL_A_BALL_INCLUDE_MESHRENDERER_H_