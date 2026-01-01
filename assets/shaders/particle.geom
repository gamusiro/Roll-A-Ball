#version 430 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec4 v_color[];
in vec2 v_uv[];
in float v_size[];
in float v_t[];

out vec4 g_color;
out vec2 g_uv;
out float g_t;

uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    vec3 position = gl_in[0].gl_Position.xyz;
    float size = v_size[0];
    
    vec3 right = vec3(u_View[0][0], u_View[1][0], u_View[2][0]);
    vec3 up    = vec3(u_View[0][1], u_View[1][1], u_View[2][1]);

    vec3 quad[4];
    quad[0] = position + (-0.5 * right - 0.5 * up) * size;
    quad[1] = position + ( 0.5 * right - 0.5 * up) * size;
    quad[2] = position + (-0.5 * right + 0.5 * up) * size;
    quad[3] = position + ( 0.5 * right + 0.5 * up) * size;

    gl_Position = u_Projection * u_View * vec4(quad[0], 1.0);
    g_uv = vec2(0.0, 0.0);
    g_t = v_t[0];
    g_color = v_color[0];
    EmitVertex();

    gl_Position = u_Projection * u_View * vec4(quad[1], 1.0);
    g_uv = vec2(1.0, 0.0);
    g_t = v_t[0];
    g_color = v_color[0];
    EmitVertex();

    gl_Position = u_Projection * u_View * vec4(quad[2], 1.0);
    g_uv = vec2(0.0, 1.0);
    g_t = v_t[0];
    g_color = v_color[0];
    EmitVertex();

    gl_Position = u_Projection * u_View * vec4(quad[3], 1.0);
    g_uv = vec2(1.0, 1.0);
    g_t = v_t[0];
    g_color = v_color[0];
    EmitVertex();

    EndPrimitive();
}
