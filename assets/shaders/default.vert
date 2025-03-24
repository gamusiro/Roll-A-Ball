#version 450 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Nor;
layout (location = 2) in vec2 a_Tex;
layout (location = 3) in vec4 a_Col;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos, 1.0);
}
