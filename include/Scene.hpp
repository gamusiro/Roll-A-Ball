#ifndef ROLL_A_BALL_INCLUDE_SCENE_HPP_
#define ROLL_A_BALL_INCLUDE_SCENE_HPP_
#include "Config.h"
#include "Scene.h"

#include "Entity.h"

template<typename T>
inline T* Scene::Instantiate(const std::string& name)
{
    std::unique_ptr<Entity> ret = std::make_unique<T>(shared_from_this());
    ret->AddComponent<Transform>(position, euler, scale);
    Tag& tag = ret->AddComponent<Tag>();
    ret->Awake();
    m_Entities.insert({ name, std::move(ret) });
    return reinterpret_cast<T*>(ret.get());
}

template<typename T>
inline T* Scene::Instantiate(
    const std::string& name,
    const glm::vec3& position,
    const glm::vec3& euler,
    const glm::vec3& scale)
{
    std::unique_ptr<Entity> ret = std::make_unique<T>(shared_from_this());
    ret->AddComponent<Transform>(position, euler, scale);
    Tag& tag = ret->AddComponent<Tag>();
    ret->Awake();
    m_Entities.insert({ name, std::move(ret) });
    return reinterpret_cast<T*>(ret.get());
}

template<typename T>
inline T* Scene::Instantiate(
    const std::string& name,
    const glm::vec3& position,
    const glm::quat& rotation,
    const glm::vec3& scale)
{
    std::unique_ptr<Entity> ret = std::make_unique<T>(shared_from_this());
    ret->AddComponent<Transform>(position, euler, scale);
    Tag& tag = ret->AddComponent<Tag>();
    ret->Awake();
    m_Entities.insert({ name, std::move(ret) });
    return reinterpret_cast<T*>(ret.get());
}

#endif //!ROLL_A_BALL_INCLUDE_SCENE_HPP_