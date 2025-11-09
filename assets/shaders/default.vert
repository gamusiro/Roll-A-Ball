#version 450 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Nor;
layout (location = 2) in vec2 a_Tex;
layout (location = 3) in vec4 a_Col;

out vec3 v_Pos;
out vec3 v_Nor;
out vec2 v_Tex;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
    // --- 法線をワールド空間へ変換 ---
    mat3 normalMatrix = transpose(inverse(mat3(u_Transform)));
    v_Nor = normalize(normalMatrix * a_Nor);

    // --- 頂点位置をワールド空間へ変換 ---
    vec4 worldPos = u_Transform * vec4(a_Pos, 1.0);
    v_Pos = worldPos.xyz;

    v_Tex = a_Tex;

    // --- クリップ空間座標へ ---
    gl_Position = u_ViewProjection * worldPos;
}
