#ifndef ROLL_A_BALL_INCLUDE_SCENE_H_
#define ROLL_A_BALL_INCLUDE_SCENE_H_
#include "Config.h"

#include "Logger.h"
#include "Utils.h"
#include "KeyEvent.h"

// Components
#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "MeshCollider.h"
#include "RigidBody.h"
#include "Material.h"
#include "Tag.h"

class Scene : public std::enable_shared_from_this<Scene>
{
public:
    Scene();
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    virtual ~Scene(){}

    virtual bool Init() = 0;
    virtual void Update() = 0;
    virtual void Render() const = 0;
    virtual void Term() = 0;

protected:
    template<typename T>
    inline std::unique_ptr<T> Instantiate();

    template<typename T>
    inline std::unique_ptr<T> Instantiate(
        const glm::vec3& position,
        const glm::vec3& euler, 
        const glm::vec3& scale);

    template<typename T>
    inline std::unique_ptr<T> Instantiate(
        const glm::vec3& position,
        const glm::quat& rotation,
        const glm::vec3& scale);

    template<typename... Types>
    decltype(auto) View()
    {
        return m_Registry.view<Types...>();
    }

    template<typename... Types>
    decltype(auto) View() const
    {
        return m_Registry.view<Types...>();
    }

private:
    entt::entity create() { return m_Registry.create(); }

    template<typename Comp, typename... Args>
    Comp& addComponent(entt::entity entity, Args&&... args)
    {
        return m_Registry.emplace<Comp>(entity, std::forward<Args>(args)...);
    }

    template<typename Comp>
    void removeComponent(entt::entity entity)
    {
        m_Registry.remove<Comp>(entity);
    }

    template<typename Comp>
    bool hasComponent(entt::entity entity)
    {
        return m_Registry.any_of<Comp>(entity);
    }

    template<typename Comp>
    Comp& getComponent(entt::entity entity)
    {
        if (!hasComponent<Comp>(entity)) {
            throw std::runtime_error("Entity doesn't have the specified component.");
        }
        return m_Registry.get<Comp>(entity);
    }

public:
    template<typename Event, typename... Args>
    void Dispatch(Args&&... args)
    {
        m_Dispatcher.trigger<Event>(std::forward<Args>(args)...);
    }

protected:
    template<typename Event, typename Value, auto Method>
    void AddEventListener(Value& value)
    {
        m_Dispatcher.sink<Event>().connect<Method>(value);
    }

    template<typename Event, typename Value, auto Method>
    void RemoveEventListener(Value& value)
    {
        m_Dispatcher.sink<Event>().disconnect<Method>(value);
    }

protected:
    std::vector<Entity*> m_StartUpEntities;

private:
    entt::registry m_Registry;
    entt::dispatcher m_Dispatcher;

private:
    friend class SceneManager;
    friend class Entity;
};

#include "Scene.hpp"

#endif //!ROLL_A_BALL_INCLUDE_SCENE_H_