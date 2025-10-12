#ifndef ROLL_A_BALL_INCLUDE_TEXTRENDERER_H_
#define ROLL_A_BALL_INCLUDE_TEXTRENDERER_H_
#include "Config.h"

#include "Component.h"

class Text;
class TextRenderer : public Component
{
public:
    TextRenderer(const std::shared_ptr<Entity> entity)
        :Component(entity){}

public:
    void Render(const Text& text) const;

private:
};

#endif //!ROLL_A_BALL_INCLUDE_TEXTRENDERER_H_