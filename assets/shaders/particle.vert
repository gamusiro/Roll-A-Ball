#version 430 core

struct Particle {
    vec3 position; float life;
    vec3 velocity; float size;
    vec4 color;
    vec3 accel; float drag;
    vec3 offset; float maxLife;
};

layout (std430, binding = 0) buffer ParticlesSsbo {
    Particle particles[];
} particlesSsboData;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 v_color;
out vec2 v_uv;
out float v_size;
out float v_t;

void main()
{
    uint particleIndex = gl_VertexID;
    Particle particle = particlesSsboData.particles[particleIndex];   

    vec3 worldPosition = (u_Model * vec4(particle.position, 1.0)).xyz;

    gl_Position = vec4(worldPosition, 1.0); 

    v_uv = vec2(0.0);
    v_size = particle.size;
    v_t = particle.life / particle.maxLife;
    v_color = particle.color;

    if (particle.life <= 0.0)
    {
        v_size = 0.0;
        return;
    }
}
