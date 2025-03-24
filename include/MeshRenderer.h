#ifndef ROLL_A_BALL_INCLUDE_MESHRENDERER_H_
#define ROLL_A_BALL_INCLUDE_MESHRENDERER_H_
#include "Config.h"

class Mesh;
class MeshRenderer
{
public:
    MeshRenderer(const Mesh& mesh);

public:
    void Render() const;

private:
    const Mesh& m_Mesh;
};

#endif //!ROLL_A_BALL_INCLUDE_MESHRENDERER_H_