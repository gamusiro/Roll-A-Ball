#ifndef ROLL_A_BALL_INCLUDE_SCENE_HPP_
#define ROLL_A_BALL_INCLUDE_SCENE_HPP_
#include "Config.h"
#include "Scene.h"

#include "Entity.h"

template<typename T>
std::unique_ptr<T> Scene::Instantiate()
{
    std::unique_ptr<T> ret = std::make_unique<T>(shared_from_this());
    Entity* entity = static_cast<Entity*>(ret.get());
    entity->AddComponent<Transform>();
    entity->Awake();
    m_StartUpEntities.push_back(entity);
    return ret;
}

#endif //!ROLL_A_BALL_INCLUDE_SCENE_HPP_