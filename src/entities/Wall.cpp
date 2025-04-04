#include "entities/Wall.h"

#include "Scene.h"
#include "Logger.h"
#include "MeshManager.h"

Wall::Wall(ScenePtr scene)
    : Entity(scene)
{
}

void Wall::Awake()
{
    Mesh& mesh = AddComponent<Mesh>(*MeshManager::Instance().Create(MODELS_PATH "Cube.obj"));
    AddComponent<MeshRenderer>(mesh);
    AddComponent<Shader>(SHADERS_PATH "default.vert", SHADERS_PATH "red.frag");

    Transform& transform = GetComponent<Transform>();

    ColliderParameter param;
    param.transform.setOrigin(VEC3_GLM_2_BT(transform.GetPosition()));
    param.transform.setRotation(QUAT_GLM_2_BT(transform.GetRotationQuat()));
    param.mass = 0.0f;
    param.friction = 0.95f;
    
    BoxCollider& collider = AddComponent<BoxCollider>(transform.GetScale(), param);
}