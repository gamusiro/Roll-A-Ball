#include "entities/Ground.h"

#include "Scene.h"
#include "Logger.h"
#include "MeshManager.h"

Ground::Ground(ScenePtr scene)
    :Entity(scene)
{
}

void Ground::Awake()
{
    Mesh& mesh = AddComponent<Mesh>(*MeshManager::Instance().Create(MODELS_PATH "Plane.obj"));
    AddComponent<MeshRenderer>(mesh);
    AddComponent<Shader>(SHADERS_PATH "default.vert", SHADERS_PATH "green.frag");

    Transform& transform = GetComponent<Transform>();

    ColliderParameter param;
    param.transform.setOrigin(VEC3_GLM_2_BT(transform.GetPosition()));
    param.transform.setRotation(QUAT_GLM_2_BT(transform.GetRotationQuat()));
    param.mass = 0.0f;
    param.friction = 1.0f;
    
    AddComponent<MeshCollider>(transform.GetScale(), mesh, param);
}