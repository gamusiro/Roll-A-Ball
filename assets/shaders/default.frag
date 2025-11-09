#version 450 core
out vec4 FragColor;

in vec3 v_Pos;
in vec3 v_Nor;
in vec2 v_Tex;

const vec3 lightCol = vec3(100.0, 100.0, 100.0);
const vec3 lightPos = vec3(0.0, 25.0, 0.0);

uniform vec3 u_CamPos;
uniform vec4 u_Albedo;

// --- 各種テクスチャ ---
uniform sampler2D u_AlbedoTexture;
uniform sampler2D u_NormalTexture;
uniform sampler2D u_RoughnessTexture;
uniform sampler2D u_MetalnessTexture;
uniform sampler2D u_DisplacementTexture;

uniform float u_HeightScale = 0.35;

// ------------------------------------------------------------
// パララックスマッピング（視差効果: DisplacementMap利用）
// ------------------------------------------------------------
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
    float height = texture(u_DisplacementTexture, texCoords).r;
    height = height * 2.0 - 1.0;
    return texCoords + viewDir.xy * height * u_HeightScale;
}

// ------------------------------------------------------------
// 法線マップからワールド空間の法線を取得
// ------------------------------------------------------------
vec3 GetNormalFromMap()
{
    vec3 tangentNormal = texture(u_NormalTexture, v_Tex).xyz * 2.0 - 1.0;

    vec3 Q1 = dFdx(v_Pos);
    vec3 Q2 = dFdy(v_Pos);
    vec2 st1 = dFdx(v_Tex);
    vec2 st2 = dFdy(v_Tex);

    vec3 N = normalize(v_Nor);
    vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B = normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

// ------------------------------------------------------------
// Fresnel, NDF, Geometry関数 (PBR用)
// ------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = 3.14159265 * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;

    return NdotV / (NdotV * (1.0 - k) + k);
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV, roughness);
    float ggx2 = GeometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}

// ------------------------------------------------------------
// main()
// ------------------------------------------------------------
void main()
{
    vec3 viewDir = normalize(u_CamPos - v_Pos);

    // 視差効果を適用
    vec2 texCoords = ParallaxMapping(v_Tex, viewDir);
    texCoords = clamp(texCoords, 0.0, 1.0);

    // 各テクスチャ読み込み
    vec3 albedo = pow(texture(u_AlbedoTexture, texCoords).rgb, vec3(2.2)) * u_Albedo.rgb;
    float roughness = texture(u_RoughnessTexture, texCoords).r;
    float metallic  = texture(u_MetalnessTexture, texCoords).r;
    vec3 N = GetNormalFromMap();

    vec3 L = normalize(lightPos - v_Pos);
    vec3 V = normalize(u_CamPos - v_Pos);
    vec3 H = normalize(L + V);
    float distance = length(lightPos - v_Pos);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = lightCol * attenuation;

    // --- PBR計算 ---
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

    float NDF = DistributionGGX(N, H, roughness);
    float G   = GeometrySmith(N, V, L, roughness);
    vec3  F   = fresnelSchlick(max(dot(H, V), 0.0), F0);

    vec3 numerator = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001;
    vec3 specular = numerator / denominator;

    vec3 kS = F;
    vec3 kD = (1.0 - kS) * (1.0 - metallic);

    float NdotL = max(dot(N, L), 0.0);
    vec3 color = (kD * albedo / 3.14159265 + specular) * radiance * NdotL;

    // 簡易的な環境光
    color += albedo * 0.03;

    // ガンマ補正
    color = pow(color, vec3(1.0 / 2.2));

    FragColor = vec4(color, 1.0);
}
