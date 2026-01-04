#version 450 core
in vec2 v_Tex;
out vec4 FragColor;

uniform sampler2D image;
uniform vec4 u_Albedo;

void main()
{
    vec4 color = texture(image, v_Tex);    
    FragColor = color;
}