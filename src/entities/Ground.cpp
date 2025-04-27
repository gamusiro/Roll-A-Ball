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
    MeshPtr mesh = MeshManager::Instance().Create(MODELS_PATH "Plane.obj");
    AddComponent<MeshRenderer>(mesh);
    
    Material& material = AddComponent<Material>();
    material.SetAlbedo(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    Tag& tag = GetComponent<Tag>();
    tag.SetName("Ground");

    Transform& transform = GetComponent<Transform>();

    ColliderParameter param;
    param.transform.setIdentity();
    param.transform.setOrigin(VEC3_GLM_2_BT(transform.GetPosition()));
    param.transform.setRotation(QUAT_GLM_2_BT(transform.GetRotationQuat()));
    param.mass = 0.0f;
    param.friction = 0.95f;
    
    AddComponent<MeshCollider>(transform.GetScale(), mesh, param);
}