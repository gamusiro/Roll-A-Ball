#version 450 core
out vec4 FragColor;

uniform vec4 u_Albedo;

void main()
{
    FragColor = u_Albedo;
}
