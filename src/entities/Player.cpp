#include "entities/Player.h"

#include "Scene.h"
#include "Logger.h"
#include "MeshManager.h"

Player::Player(ScenePtr scene)
    : Entity(scene)
{
}

void Player::Awake()
{
    Mesh& mesh = AddComponent<Mesh>(*MeshManager::Instance().Create(MODELS_PATH "Sphere.obj"));
    AddComponent<MeshRenderer>(mesh);
    AddComponent<Shader>(SHADERS_PATH "default.vert", SHADERS_PATH "white.frag");

    Transform& transform = GetComponent<Transform>();

    ColliderParameter param;
    param.transform.setOrigin(VEC3_GLM_2_BT(transform.GetPosition()));
    param.transform.setRotation(QUAT_GLM_2_BT(transform.GetRotationQuat()));
    param.mass = 1.0f;
    param.friction = 1.0f;
    
    const float radius = 1.0f;
    SphereCollider& collider = AddComponent<SphereCollider>(radius, param);
    AddComponent<RigidBody>(collider);
}