#version 450 core
out vec4 FragColor;

in vec3 v_Pos;
in vec3 v_Nor;

const vec3 lightCol = vec3(1.0, 1.0, 1.0);
const vec3 lightPos = vec3(0.0, 25.0, 5.0);

uniform vec4 u_Albedo;

void main()
{
    vec3 lightDir = normalize(lightPos - v_Pos);

    float diff = max(dot(v_Nor, lightDir), 0.0);
    vec3 diffuse = diff * lightCol;

    vec4 result = vec4(diffuse, 1.0) * u_Albedo;
    FragColor = result;
}
