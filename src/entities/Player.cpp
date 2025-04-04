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
    
    const float radius = 0.5f;
    SphereCollider& collider = AddComponent<SphereCollider>(radius, param);
    AddComponent<RigidBody>(collider);
}

void Player::KeyPressed(const KeyEventPressed& e)
{
    LOG_CORE_INFO("KeyEvent!!!");

    RigidBody& rigidBody = GetComponent<RigidBody>();
    Transform& transform = GetComponent<Transform>();

    std::stringstream ss;
    ss << "x: " << transform.GetPosition().x << " y: " << transform.GetPosition().y << " z: " << transform.GetPosition().z << std::endl;
    LOG_CORE_INFO(ss.str());

    if(e.GetKeyCode() == GLFW_KEY_W){
        rigidBody.AddImpulse(transform.GetForward());
    }
    else if(e.GetKeyCode() == GLFW_KEY_S){
        rigidBody.AddImpulse(transform.GetForward() * -1.0f);
    }
    else if(e.GetKeyCode() == GLFW_KEY_A){
        rigidBody.AddImpulse(transform.GetRight() * -1.0f);
    }
    else if(e.GetKeyCode() == GLFW_KEY_D){
        rigidBody.AddImpulse(transform.GetRight());
    }
}

void Player::KeyReleased(const KeyEventReleased& e)
{

}