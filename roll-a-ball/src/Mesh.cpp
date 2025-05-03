#include "Mesh.h"

#include "Logger.h"

Mesh::Mesh(
    const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices,
    uint32_t vao, uint32_t vbo, uint32_t ebo)
    : m_Vertices(vertices), m_Indices(indices),
    m_VAO(vao), m_VBO(vbo), m_EBO(ebo)
{
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_EBO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}