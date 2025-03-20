#include "entities/Player.h"

#include "Scene.h"
#include "Logger.h"

Player::Player(ScenePtr scene)
    : Entity(scene)
{
}

void Player::Update()
{
    Transform& transform = GetComponent<Transform>();
    glm::vec3 pos = transform.GetPosition();
    pos.x += 1.0f;
    transform.SetPosition(pos);
}