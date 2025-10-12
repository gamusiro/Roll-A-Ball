#version 450 core
in vec2 v_Tex;
out vec4 FragColor;

uniform sampler2D text;
uniform vec4 u_Albedo;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, v_Tex).r);
    FragColor = u_Albedo * sampled;
}
