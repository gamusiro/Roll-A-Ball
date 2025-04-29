#include "entities/Collectable.h"

#include "Scene.h"
#include "Logger.h"
#include "MeshManager.h"

Collectable::Collectable(ScenePtr scene)
    :Entity(scene)
{
}

void Collectable::Awake()
{
    MeshPtr mesh = MeshManager::Instance().Create(MODELS_PATH "Cube.obj");
    AddComponent<MeshRenderer>(mesh);

    Material& material = AddComponent<Material>();
    material.SetAlbedo(glm::vec4(255.0f / 255.0f, 242.0f / 255.0f, 0.0f, 1.0f));

    Tag& tag = GetComponent<Tag>();
    tag.SetName("Collectable");

    Transform& transform = GetComponent<Transform>();

    ColliderParameter param;
    param.transform.setIdentity();
    param.transform.setOrigin(VEC3_GLM_2_BT(transform.GetPosition()));
    param.transform.setRotation(QUAT_GLM_2_BT(transform.GetRotationQuat()));
    param.mass = 0.0f;
    param.friction = 0.95f;
    param.isTrigger = true;
    
    BoxCollider& collider = AddComponent<BoxCollider>(transform.GetScale(), param);
}

void Collectable::Update()
{
    Transform& transform = GetComponent<Transform>();
    glm::quat currentQuat = transform.GetRotationQuat();
    glm::quat deltaRotXY = glm::angleAxis(glm::radians(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    transform.SetRotation(deltaRotXY * currentQuat);
}

void Collectable::OnTriggerEnter(const Entity* entity)
{
    Tag& tag = entity->GetComponent<Tag>();
    if(tag.GetName() == "Player")
    {
        std::cout << "Hit Player object!!!" << std::endl;
        RemoveComponent<MeshRenderer>();
    }
}