#include "entities/Wall.h"

#include "Scene.h"
#include "Logger.h"
#include "MeshManager.h"
#include "TextureManager.h"

Wall::Wall(ScenePtr scene)
    : Entity(scene)
{
}

void Wall::Awake()
{
    MeshPtr mesh = MeshManager::Instance().Create(MODELS_PATH "Cube.obj");
    AddComponent<MeshRenderer>(mesh);


    TextureManager& tm = TextureManager::Instance();
    Material& material = AddComponent<Material>();
    material.SetAlbedo(glm::vec4(1.0f));
    material.SetAlbedoTexture(tm.GetTexture(TEXTURE_WALL_ALBEDO));
    material.SetNormalTexture(tm.GetTexture(TEXTURE_WALL_NORMAL));
    material.SetRoughnessTexture(tm.GetTexture(TEXTURE_WALL_ROUGHNESS));
    material.SetDisplacementTexture(tm.GetTexture(TEXTURE_WALL_DISPLACEMENT));

    Tag& tag = GetComponent<Tag>();
    tag.SetName("Wall");

    Transform& transform = GetComponent<Transform>();

    ColliderParameter param;
    param.transform.setOrigin(VEC3_GLM_2_BT(transform.GetPosition()));
    param.transform.setRotation(QUAT_GLM_2_BT(transform.GetRotationQuat()));
    param.mass = 0.0f;
    param.friction = 0.95f;
    
    BoxCollider& collider = AddComponent<BoxCollider>(transform.GetScale(), param);
}