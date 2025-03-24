#include "MeshManager.h"
#include "Logger.h"

MeshManager& MeshManager::Instance()
{
    static MeshManager instance;
    return instance;
}

std::shared_ptr<Mesh> MeshManager::Create(const std::string& fileName)
{
    LOG_CORE_INFO("MeshManager::Create");

    // Already loaded
    if(m_Meshes.find(fileName) != m_Meshes.end()){
        LOG_CORE_INFO("MeshManager::Create Already Loaded");
        return m_Meshes.at(fileName);
    }

    // Load file
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    LOG_CORE_INFO("MeshManager::Create Load file " + fileName);
    if(!loadModel(fileName, vertices, indices))
    {
        LOG_CORE_ERROR("Failed tp load file");
        std::abort();
    }

    uint32_t VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    uint32_t stride = sizeof(Vertex);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride), (void*)offsetof(Vertex, Position));

    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride), (void*)offsetof(Vertex, Normal));

    // TexCoord
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride), (void*)offsetof(Vertex, TexCoords));

    // Color
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride), (void*)offsetof(Vertex, Color));

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

    std::shared_ptr<Mesh> ret = std::make_shared<Mesh>(vertices, indices, VAO, VBO, EBO);
    m_Meshes.emplace(fileName, ret);
    return ret;
}

void MeshManager::Clear()
{
    LOG_CORE_INFO("MeshManager::Clear");
    m_Meshes.clear();
}

bool MeshManager::loadModel(const std::string& fileName, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        LOG_CORE_ERROR(importer.GetErrorString());
        return false;
    }

    aiMesh* mesh = scene->mMeshes[0];
    vertices.resize(mesh->mNumVertices);
    for(unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        // Positions
        vertices[i].Position.x = mesh->mVertices[i].x;
        vertices[i].Position.y = mesh->mVertices[i].y;
        vertices[i].Position.z = mesh->mVertices[i].z;
        
        // normals
        if (mesh->HasNormals())
        {
            vertices[i].Normal.x = mesh->mNormals[i].x;
            vertices[i].Normal.y = mesh->mNormals[i].y;
            vertices[i].Normal.z = mesh->mNormals[i].z;
        }

        // Colors
        if(mesh->HasVertexColors(i))
        {
            vertices[i].Color.r = mesh->mColors[i]->r;
            vertices[i].Color.g = mesh->mColors[i]->g;
            vertices[i].Color.b = mesh->mColors[i]->b;
            vertices[i].Color.a = mesh->mColors[i]->a;
        }
        else
        {
            vertices[i].Color = glm::vec4(1.0f);
        }
        
        // texture coordinates
        if(mesh->mTextureCoords[0])
        {
            vertices[i].TexCoords.x = mesh->mTextureCoords[0][i].x; 
            vertices[i].TexCoords.y = mesh->mTextureCoords[0][i].y;
        }
        else
        {
            vertices[i].TexCoords = glm::vec2(0.0f, 0.0f);
        }
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);        
    }

    return true;
}