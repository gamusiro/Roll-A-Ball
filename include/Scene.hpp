#ifndef ROLL_A_BALL_INCLUDE_SCENE_HPP_
#define ROLL_A_BALL_INCLUDE_SCENE_HPP_
#include "Config.h"
#include "Scene.h"

#include "Entity.h"

template<typename T>
inline std::shared_ptr<T> Scene::Instantiate(const std::string& name)
{
    std::shared_ptr<T> ret = std::make_shared<T>(shared_from_this());
    ret->AddComponent<Transform>(position, euler, scale);
    ret->AddComponent<Tag>();
    ret->Awake();
    ret.get()->m_Name = name;
    m_Entities.insert({ name, std::static_pointer_cast<Entity>(ret) });
    return ret;
}

template<typename T>
inline std::shared_ptr<T> Scene::Instantiate(
    const std::string& name,
    const glm::vec3& position,
    const glm::vec3& euler,
    const glm::vec3& scale)
{
    std::shared_ptr<T> ret = std::make_shared<T>(shared_from_this());
    ret->AddComponent<Transform>(position, euler, scale);
    ret->AddComponent<Tag>();
    ret->Awake();
    ret.get()->m_Name = name;
    m_Entities.insert({ name, std::static_pointer_cast<Entity>(ret) });
    return ret;
}

template<typename T>
inline std::shared_ptr<T> Scene::Instantiate(
    const std::string& name,
    const glm::vec3& position,
    const glm::quat& rotation,
    const glm::vec3& scale)
{
    std::shared_ptr<T> ret = std::make_shared<T>(shared_from_this());
    ret->AddComponent<Transform>(position, euler, scale);
    ret->AddComponent<Tag>();
    ret->Awake();
    ret.get()->m_Name = name;
    m_Entities.insert({ name, std::static_pointer_cast<Entity>(ret) });
    return ret;
}

#endif //!ROLL_A_BALL_INCLUDE_SCENE_HPP_