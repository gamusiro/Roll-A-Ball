#include "Text.h"

Text::Text(const std::shared_ptr<Entity> entity, const std::u32string& text, FontPtr font)
        :Component(entity), m_Text(text), m_Font(font) 
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBOPos);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOPos);

    glGenBuffers(1, &m_VBOTex);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOTex);
    
    // Position attribute
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOPos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 6, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBOTex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 6, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Text::~Text()
{
    glDeleteBuffers(1, &m_VBOTex);
    glDeleteBuffers(1, &m_VBOPos);
    glDeleteBuffers(1, &m_VAO);
}