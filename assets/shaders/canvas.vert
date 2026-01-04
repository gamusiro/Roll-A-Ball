#version 450 core
layout (location = 0) in vec4 a_Vert;

out vec2 v_Tex;

uniform mat4 u_Model;
uniform mat4 u_Projection;

void main() {
    gl_Position = u_Projection * u_Model * vec4(a_Vert.xy, 0.0, 1.0);
    v_Tex = a_Vert.zw;
}