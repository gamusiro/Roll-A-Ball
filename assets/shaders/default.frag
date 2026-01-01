#version 450 core
out vec4 FragColor;

in vec3 v_Pos;
in vec3 v_Nor;
in vec2 v_Tex;

uniform vec3 u_CamPos;
uniform vec4 u_Albedo;

uniform sampler2D u_AlbedoTexture;
uniform sampler2D u_NormalTexture;
uniform sampler2D u_RoughnessTexture;
uniform sampler2D u_MetalnessTexture;
uniform sampler2D u_DisplacementTexture;

void main()
{    
    vec3 albedo = texture(u_AlbedoTexture, v_Tex).rgb * u_Albedo.rgb;
    FragColor = vec4(albedo, 1.0);
}
