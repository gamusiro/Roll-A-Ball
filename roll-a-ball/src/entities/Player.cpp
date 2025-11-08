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
    MeshPtr mesh = MeshManager::Instance().Create(MODELS_PATH "Sphere.obj");
    AddComponent<MeshRenderer>(mesh);
    
    Material& material = AddComponent<Material>();
    material.SetAlbedo(glm::vec4(1.0f));

    Tag& tag = GetComponent<Tag>();
    tag.SetName("Player");

    Transform& transform = GetComponent<Transform>();

    ColliderParameter param;
    param.transform.setOrigin(VEC3_GLM_2_BT(transform.GetPosition()));
    param.transform.setRotation(QUAT_GLM_2_BT(transform.GetRotationQuat()));
    param.mass = 1.0f;
    param.friction = 1.0f;
    
    const float radius = 0.5f;
    SphereCollider& collider = AddComponent<SphereCollider>(radius, param);
    AddComponent<RigidBody>(collider);

    InputAction moveAction(
        "Move",
        { InputPath::Keyboard::W, InputPath::Keyboard::S, InputPath::Keyboard::A, InputPath::Keyboard::D },
        std::make_shared<Vector2Composite>(InputPath::Keyboard::W, InputPath::Keyboard::S, InputPath::Keyboard::A, InputPath::Keyboard::D),
        std::bind(&Player::Move, this, std::placeholders::_1));

    InputAction jumpAction(
        "Jump", 
        { InputPath::Keyboard::SPACE }, 
        std::make_shared<ButtonComposite>(InputPath::Keyboard::SPACE),
        std::bind(&Player::Jump, this, std::placeholders::_1));

    PlayerInput& playerInput = AddComponent<PlayerInput>();
    playerInput.AddAction(moveAction);
    playerInput.AddAction(jumpAction);
}

void Player::Move(const InputActionCallbackContext& context)
{
    glm::vec2 inputDir = context.ReadValue<glm::vec2>();
    std::cout << "X: " << inputDir.x << " Y: " << inputDir.y << std::endl;

    RigidBody& rigidBody = GetComponent<RigidBody>();
    Transform& transform = GetComponent<Transform>();

    glm::vec3 fwd = transform.GetForward() * inputDir.y;
    glm::vec3 rgt = transform.GetRight() * inputDir.x;

    rigidBody.AddImpulse((fwd + rgt) * k_Speed);
}

void Player::Jump(const InputActionCallbackContext& context)
{
    bool jump = context.ReadValue<bool>();
    std::cout << "Player::Jump" << std::endl;
}
