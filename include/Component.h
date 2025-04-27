#ifndef ROLL_A_BALL_INCLUDE_COMPONENT_H_
#define ROLL_A_BALL_INCLUDE_COMPONENT_H_

class Entity;
class Component
{
public:
    Component() = delete;
    virtual ~Component() = default;

protected:
    const Entity& GetEntity() { return m_Entity; }
    const Entity& GetEntity() const { return m_Entity; }

protected:
    Component(const Entity* entity) : m_Entity(*entity){}

private:
    const Entity& m_Entity;
};

#endif //!ROLL_A_BALL_INCLUDE_COMPONENT_H_