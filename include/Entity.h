#ifndef ROLL_A_BALL_INCLUDE_ENTITY_H_
#define ROLL_A_BALL_INCLUDE_ENTITY_H_
#include "Config.h"
#include "Scene.h"

class Entity
{
public:
    Entity(ScenePtr scene);
    virtual ~Entity(){}

public:
    virtual void Awake(){}
    virtual void Start(){}
    virtual void Update(){}
    virtual void OnCollisionEnter(const Entity* entity){}
    virtual void OnCollisionStay(const Entity* entity){}
    virtual void OnCollisionExit(const Entity* entity){}
    virtual void OnTriggerEnter(const Entity* entity){}
    virtual void OnTriggerStay(const Entity* entity){}
    virtual void OnTriggerExit(const Entity* entity){}

public:
    template<typename Comp, typename... Args>
    Comp& AddComponent(Args&&... args)
    {
        return m_Scene->addComponent<Comp>(m_ID, this, std::forward<Args>(args)...);
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

private:
    entt::entity m_ID;
    ScenePtr m_Scene;
};

#endif