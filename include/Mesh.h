#ifndef ROLL_A_BALL_INCLUDE_MESH_H_
#define ROLL_A_BALL_INCLUDE_MESH_H_
#include "Config.h"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec4 Color; 
};

class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, uint32_t vao, uint32_t vbo, uint32_t ebo);
    ~Mesh();

public:
    inline uint32_t GetVertexArray() const { return m_VAO; }
    inline uint32_t GetVertexBuffer() const { return m_VBO; }
    inline uint32_t GetIndexBuffer() const { return m_EBO; }
    inline size_t GetVertexCount() const { return m_Vertices.size(); }
    inline size_t GetIndexCount() const { return m_Indices.size(); }
    inline const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
    inline const std::vector<uint32_t>& GetIndices() const { return m_Indices; }

private:
    std::vector<Vertex> m_Vertices;
    std::vector<uint32_t> m_Indices;

    uint32_t m_VAO;
    uint32_t m_VBO;
    uint32_t m_EBO;
};


#endif //!ROLL_A_BALL_INCLUDE_MESH_H_