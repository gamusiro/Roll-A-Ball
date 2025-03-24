#include "MeshRenderer.h"

#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"

MeshRenderer::MeshRenderer(const Mesh& mesh)
    :m_Mesh(mesh)
{
}

void MeshRenderer::Render() const
{
    glBindVertexArray(m_Mesh.GetVertexArray());
    glDrawElements(GL_TRIANGLES, m_Mesh.GetIndexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}