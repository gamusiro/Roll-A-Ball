#ifndef ROLL_A_BALL_INCLUDE_SCENE_H_
#define ROLL_A_BALL_INCLUDE_SCENE_H_
#include "Config.h"

#include "Logger.h"
#include "Utils.h"
#include "Entity.h"

// Components
#include "Transform.h"

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
    inline std::unique_ptr<T> Instantiate()
    {
        std::unique_ptr<T> ret = std::make_unique<T>(shared_from_this());
        static_cast<Entity*>(ret.get())->AddComponent<Transform>();
        return ret;
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

private:
    entt::registry m_Registry;

private:
    friend class Entity;
};

#endif //!ROLL_A_BALL_INCLUDE_SCENE_H_