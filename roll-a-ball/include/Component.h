#ifndef ROLL_A_BALL_INCLUDE_COMPONENT_H_
#define ROLL_A_BALL_INCLUDE_COMPONENT_H_
#include "Config.h"

class Component
{
public:
    Component() = delete;
    virtual ~Component() = default;

public:
    const std::shared_ptr<Entity> GetEntity() { return m_Entity; }
    const std::shared_ptr<Entity> GetEntity() const { return m_Entity; }

protected:
    Component(const std::shared_ptr<Entity> entity) : m_Entity(entity){}

private:
    const std::shared_ptr<Entity> m_Entity;
};

#endif //!ROLL_A_BALL_INCLUDE_COMPONENT_H_