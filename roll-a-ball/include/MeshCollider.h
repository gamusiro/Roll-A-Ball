#ifndef ROLL_A_BALL_INCLUDE_MESHCOLLIDER_H_
#define ROLL_A_BALL_INCLUDE_MESHCOLLIDER_H_
#include "Config.h"

#include "Collider.h"
#include "Mesh.h"

class MeshCollider : public Collider
{
public:
    MeshCollider(const std::shared_ptr<Entity> entity, const glm::vec3& scale, const MeshPtr& mesh, const ColliderParameter& parameter);
    ~MeshCollider();

private:
    btTriangleMesh* m_Mesh;
};

#endif //!ROLL_A_BALL_INCLUDE_MESHCOLLIDER_H_