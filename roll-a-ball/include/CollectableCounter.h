#ifndef ROLL_A_BALL_INCLUDE_COLLECTABLECOUNTER_H_
#define ROLL_A_BALL_INCLUDE_COLLECTABLECOUNTER_H_
#include "Config.h"

#include "Component.h"

class CollectableCounter : public Component
{
public:
    CollectableCounter(const std::shared_ptr<Entity> entity, int val = 0)
        :Component(entity), m_Value(val){}

    void SetValue(int val) { m_Value = val; }
    int GetValue() { return m_Value; }

private:
    int m_Value;
};

#endif //!ROLL_A_BALL_INCLUDE_COLLECTABLECOUNTER_H_