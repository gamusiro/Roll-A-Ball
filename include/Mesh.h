#ifndef ROLL_A_BALL_INCLUDE_MESH_H_
#define ROLL_A_BALL_INCLUDE_MESH_H_
#include "Config.h"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
    glm::vec4 Color;
    float weights[4];
    USHORT joints[4]; 
};


#endif //!ROLL_A_BALL_INCLUDE_MESH_H_