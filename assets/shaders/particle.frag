#version 430 core
out vec4 fragColor;

in vec4 g_color;
in vec2 g_uv;
in float g_t;

uniform sampler2D u_Particle;
uniform sampler2D u_ColorOverLifeGradient;

void main()
{
    vec4 particle = texture(u_Particle, g_uv);
    vec4 color = texture(u_ColorOverLifeGradient, vec2(1.0f - g_t, 0.0));
    fragColor = particle * vec4(color.rgb * g_color.rgb, color.a * g_t);
}
