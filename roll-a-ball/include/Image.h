#ifndef ROLL_A_BALL_INCLUDE_IMAGE_H_
#define ROLL_A_BALL_INCLUDE_IMAGE_H_
#include "Config.h"

#include "Component.h"

class Image : public Component
{
public:
    Image(const std::shared_ptr<Entity> entity);
    ~Image();

public:
    void SetSourceImage(const std::string& textureName);
    void SetColor(const glm::vec4& color);

private:
    TexturePtr m_SourceImage;
    glm::vec4 m_Color;

private:
    friend class CanvasRenderer;
};

#endif //!ROLL_A_BALL_INCLUDE_IMAGE_H_