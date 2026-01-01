#version 430 core
out vec4 fragColor;

in vec4 g_color;
in vec2 g_uv;
in float g_t;

void main()
{
    fragColor = vec4(g_color.rgb, g_t);
}
