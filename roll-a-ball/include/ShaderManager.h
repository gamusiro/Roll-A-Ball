#ifndef ROLL_A_BALL_INCLUDE_SHADERMANAGER_H_
#define ROLL_A_BALL_INCLUDE_SHADERMANAGER_H_
#include "Config.h"
#include "Shader.h"

class ShaderManager
{
public:
    static ShaderManager& Instance();
    void LoadShader(const std::string& shaderName, const std::string& vertName, const std::string& fragName);
    ShaderPtr GetShader(const std::string& shaderName);
    void Clear();

private:
    ShaderManager() = default;
    ~ShaderManager() = default;
    ShaderManager(const ShaderManager&) = delete;
    ShaderManager operator= (const ShaderManager&) = delete;

private:
    std::unordered_map<std::string, ShaderPtr> m_Shaders; 
};

#endif //!ROLL_A_BALL_INCLUDE_SHADERMANAGER_H_