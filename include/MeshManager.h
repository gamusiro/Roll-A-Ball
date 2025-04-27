#ifndef ROLL_A_BALL_INCLUDE_MESHMANAGER_H_
#define ROLL_A_BALL_INCLUDE_MESHMANAGER_H_
#include "Config.h"
#include "Mesh.h"

class MeshManager
{
public:
    static MeshManager& Instance();
    MeshPtr Create(const std::string& fileName);
    void Clear();

private:
    bool loadModel(const std::string& fileName, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

private:
    MeshManager() = default;
    ~MeshManager() = default;
    MeshManager(const MeshManager&) = delete;
    MeshManager operator= (const MeshManager&) = delete;

private:
    std::unordered_map<std::string, MeshPtr> m_Meshes; 
};

#endif //!ROLL_A_BALL_INCLUDE_MESHMANAGER_H_