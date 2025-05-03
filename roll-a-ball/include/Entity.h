#ifndef ROLL_A_BALL_INCLUDE_ENTITY_H_
#define ROLL_A_BALL_INCLUDE_ENTITY_H_
#include "Config.h"
#include "Scene.h"

class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity(ScenePtr scene);
    virtual ~Entity() {}

public:
    virtual void Awake(){}
    virtual void Start(){}
    virtual void Update(){}
    virtual void OnCollisionEnter(const std::shared_ptr<Entity> entity){}
    virtual void OnCollisionStay(const std::shared_ptr<Entity> entity){}
    virtual void OnCollisionExit(const std::shared_ptr<Entity> entity){}
    virtual void OnTriggerEnter(const std::shared_ptr<Entity> entity){}
    virtual void OnTriggerStay(const std::shared_ptr<Entity> entity){}
    virtual void OnTriggerExit(const std::shared_ptr<Entity> entity){}

public:
    template<typename Comp, typename... Args>
    Comp& AddComponent(Args&&... args)
    {
        return m_Scene->addComponent<Comp>(m_ID, shared_from_this(), std::forward<Args>(args)...);
    }

    template<typename Comp>
    void RemoveComponent()
    {
        m_Scene->removeComponent<Comp>(m_ID);
    }

    template<typename Comp>
    bool HasComponent() const
    {
        return m_Scene->hasComponent<Comp>(m_ID);
    }

    template<typename Comp>
    Comp& GetComponent() const
    {
        return m_Scene->getComponent<Comp>(m_ID);
    }

    inline void Destroy(const std::shared_ptr<Entity> entity)
    {
        m_Scene->Destroy(entity);
    }

private:
    std::string m_Name;
    entt::entity m_ID;
    ScenePtr m_Scene;
    friend class Scene;
};

#endif