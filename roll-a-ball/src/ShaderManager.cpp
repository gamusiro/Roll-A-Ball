#include "ShaderManager.h"
#include "Logger.h"

ShaderManager& ShaderManager::Instance()
{
    static ShaderManager instance;
    return instance;
}

void ShaderManager::LoadShader(const std::string& shaderName, const std::string& compName)
{
    if(isShaderLoaded(shaderName))
        return;

    ShaderPtr shader = std::make_shared<Shader>((SHADERS_PATH + compName).c_str());
    m_Shaders[shaderName] = shader;
    LOG_CORE_INFO("ShaderManager::LoadShader Success to load " + shaderName);
}

void ShaderManager::LoadShader(const std::string& shaderName, const std::string& vertName, const std::string& fragName)
{
    if(isShaderLoaded(shaderName))
        return;

    ShaderPtr shader = std::make_shared<Shader>((SHADERS_PATH + vertName).c_str(), (SHADERS_PATH + fragName).c_str());
    m_Shaders[shaderName] = shader;
    LOG_CORE_INFO("ShaderManager::LoadShader Success to load " + shaderName);
}

void ShaderManager::LoadShader(const std::string& shaderName, const std::string& vertName, const std::string& geomName, const std::string& fragName)
{
    if(isShaderLoaded(shaderName))
        return;

    ShaderPtr shader = std::make_shared<Shader>((SHADERS_PATH + vertName).c_str(), (SHADERS_PATH + geomName).c_str(), (SHADERS_PATH + fragName).c_str());
    m_Shaders[shaderName] = shader;
    LOG_CORE_INFO("ShaderManager::LoadShader Success to load " + shaderName);
}

ShaderPtr ShaderManager::GetShader(const std::string& shaderName)
{
    if(m_Shaders.find(shaderName) == m_Shaders.end())
    {
        LOG_CORE_ERROR("ShaderManager::GetShader Not Exists " + shaderName);
        return nullptr;
    }

    return m_Shaders.at(shaderName);
}

void ShaderManager::Clear()
{
    LOG_CORE_INFO("ShaderManager::Clear");
    m_Shaders.clear();
}

bool ShaderManager::isShaderLoaded(const std::string& shaderName)
{
    if(m_Shaders.find(shaderName) != m_Shaders.end())
    {
        LOG_CORE_WARN("ShaderManager::LoadShader Already loaded " + shaderName);
        return true;
    }
    return false;
}