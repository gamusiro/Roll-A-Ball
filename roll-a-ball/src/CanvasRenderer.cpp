#include "CanvasRenderer.h"

#include "Text.h"
#include "Image.h"
#include "Texture.h"
#include "RectTransform.h"
#include "ShaderManager.h"

CanvasRenderer::CanvasRenderer(const std::shared_ptr<Entity> entity)
    :Component(entity),
    m_Shader(ShaderManager::Instance().GetShader(RENDERER_SHADER_CANVAS))
{
    glm::vec4 quadVertices[6] = {
        { -0.5f,  0.5f,  0.0f, 0.0f },
        { -0.5f, -0.5f,  0.0f, 1.0f },
        {  0.5f, -0.5f,  1.0f, 1.0f },

        { -0.5f,  0.5f,  0.0f, 0.0f },
        {  0.5f, -0.5f,  1.0f, 1.0f },
        {  0.5f,  0.5f,  1.0f, 0.0f }
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

CanvasRenderer::~CanvasRenderer()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void CanvasRenderer::Render(const glm::mat4& proj, const RectTransform& transform, const Text& text) const
{

    m_Shader->Bind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, text.m_Renderer.GetTextureID());

    glm::mat4 model = transform.GetWorldMatrix();
    model *= glm::scale(glm::mat4(1.0f), glm::vec3(transform.GetSize(), 1.0f));
    m_Shader->Set("u_Albedo", glm::vec4(1.0f));
    m_Shader->Set("u_Model", model);
    m_Shader->Set("u_Projection", proj);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_Shader->Unbind();
}

void CanvasRenderer::Render(const glm::mat4& proj, const RectTransform& transform, const Image& image) const
{
    m_Shader->Bind();

    glActiveTexture(GL_TEXTURE0);
    image.m_SourceImage->Bind();

    glm::mat4 model = transform.GetWorldMatrix();
    model *= glm::scale(glm::mat4(1.0f), glm::vec3(transform.GetSize(), 1.0f));
    m_Shader->Set("u_Albedo", image.m_Color);
    m_Shader->Set("u_Model", model);
    m_Shader->Set("u_Projection", proj);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_Shader->Unbind();
}
