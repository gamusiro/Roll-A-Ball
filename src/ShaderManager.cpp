#include "ShaderManager.h"
#include "Logger.h"

ShaderManager& ShaderManager::Instance()
{
    static ShaderManager instance;
    return instance;
}

void ShaderManager::LoadShader(const std::string& shaderName, const std::string& vertName, const std::string& fragName)
{
    ShaderPtr shader = std::make_shared<Shader>((SHADERS_PATH + vertName).c_str(), (SHADERS_PATH + fragName).c_str());
    if(m_Shaders.find(shaderName) != m_Shaders.end())
    {
        LOG_CORE_WARN("ShaderManager::LoadShader Already loaded " + shaderName);
        return;
    }

    LOG_CORE_INFO("ShaderManager::LoadShader Success to load " + shaderName);
    m_Shaders[shaderName] = shader;
}

ShaderPtr ShaderManager::GetShader(const std::string& shaderName)
{
    return m_Shaders.at(shaderName);
}

void ShaderManager::Clear()
{
    LOG_CORE_INFO("ShaderManager::Clear");
    m_Shaders.clear();
}