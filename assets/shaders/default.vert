#version 450 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Nor;
layout (location = 2) in vec2 a_Tex;
layout (location = 3) in vec4 a_Col;

out vec3 v_Pos;
out vec3 v_Nor;
out vec2 v_Tex;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
    vec4 worldPos = u_Model * vec4(a_Pos, 1.0);

    gl_Position = u_Projection * u_View * worldPos;

    v_Pos = worldPos.xyz;
    v_Tex = a_Tex;
    v_Nor = normalize(normalMatrix * a_Nor);
}
