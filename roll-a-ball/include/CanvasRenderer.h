#ifndef ROLL_A_BALL_INCLUDE_CANVAS_RENDERER_H_
#define ROLL_A_BALL_INCLUDE_CANVAS_RENDERER_H_
#include "Config.h"

#include "Component.h"

class Text;
class RectTransform;
class CanvasRenderer : public Component
{
public:
    CanvasRenderer(const std::shared_ptr<Entity> entity);
    ~CanvasRenderer();

public:
    void Render(const glm::mat4& proj, const RectTransform& transform, const Text& text) const;

private:
    GLuint m_VAO;
    GLuint m_VBO;
    ShaderPtr m_Shader;
};


#endif //!ROLL_A_BALL_INCLUDE_CANVAS_RENDERER_H_