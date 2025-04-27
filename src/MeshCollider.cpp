#include "MeshCollider.h"

MeshCollider::MeshCollider(const Entity* entity, const glm::vec3& scale, const MeshPtr& mesh, const ColliderParameter& parameter)
    : Collider(entity)
{
    m_Mesh = new btTriangleMesh();
    const std::vector<Vertex> vertices = mesh->GetVertices();
    const std::vector<uint32_t> indices = mesh->GetIndices();
    for(int i = 0; i < mesh->GetIndexCount(); i += 3)
    {
        btVector3 vertex1 = VEC3_GLM_2_BT(vertices[indices[i + 0]].Position);
        btVector3 vertex2 = VEC3_GLM_2_BT(vertices[indices[i + 1]].Position);
        btVector3 vertex3 = VEC3_GLM_2_BT(vertices[indices[i + 2]].Position);
        m_Mesh->addTriangle(vertex1, vertex2, vertex3);
    }

    m_Shape = new btBvhTriangleMeshShape(m_Mesh, true);
    m_Shape->setLocalScaling(VEC3_GLM_2_BT(scale));

    btVector3 localInetia(0.0f, 0.0f, 0.0f);
    if (parameter.mass != 0.0f) {
        m_Shape->calculateLocalInertia(parameter.mass, localInetia);
    }

    btDefaultMotionState* motion = new btDefaultMotionState(parameter.transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(parameter.mass, motion, m_Shape, localInetia);
    m_RigidBody = new btRigidBody(rbInfo);
    m_RigidBody->setFriction(parameter.friction);

    Physics::Instance().AddRigidBody(m_RigidBody);
}

MeshCollider::~MeshCollider()
{
    delete m_Mesh;
}