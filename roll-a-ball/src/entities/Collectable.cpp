#include "entities/Collectable.h"

#include "Scene.h"
#include "Logger.h"
#include "MeshManager.h"
#include "TextureManager.h"

Collectable::Collectable(ScenePtr scene)
    :Entity(scene)
{
}

void Collectable::Awake()
{
    MeshPtr mesh = MeshManager::Instance().Create(MODELS_PATH "Cube.obj");
    AddComponent<MeshRenderer>(mesh);

    TextureManager& tm = TextureManager::Instance();
    Material& material = AddComponent<Material>();
    material.SetAlbedo(glm::vec4(1.0f));
    material.SetAlbedoTexture(tm.GetTexture(TEXTURE_COLLECTABLE_ALBEDO));
    material.SetNormalTexture(tm.GetTexture(TEXTURE_COLLECTABLE_NORMAL));
    material.SetRoughnessTexture(tm.GetTexture(TEXTURE_COLLECTABLE_ROUGHNESS));
    material.SetDisplacementTexture(tm.GetTexture(TEXTURE_COLLECTABLE_DISPLACEMENT));

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

void Collectable::OnTriggerEnter(const std::shared_ptr<Entity> entity)
{
    Tag& tag = entity->GetComponent<Tag>();
    if(tag.GetName() == "Player")
    {
        LOG_CORE_TRACE("Hit Player object!!!");

        auto counterEntt = FindEntity<Entity>("Counter");
        CollectableCounter& cc = counterEntt->GetComponent<CollectableCounter>();
        cc.SetValue(cc.GetValue() - 1);

        Destroy(shared_from_this());
    }
}