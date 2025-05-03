#ifndef ROLL_A_BALL_INCLUDE_TAG_H_ 
#define ROLL_A_BALL_INCLUDE_TAG_H_
#include "Config.h"

#include "Component.h"

class Tag : public Component
{
public:
    Tag(const std::shared_ptr<Entity> entity) : Component(entity), m_Name("Untagged") {}
    ~Tag(){}

    inline void SetName(const std::string& name) { m_Name = name; }
    inline const std::string& GetName() const { return m_Name; }

private:
    std::string m_Name;
};

#endif //!ROLL_A_BALL_INCLUDE_TAG_H_