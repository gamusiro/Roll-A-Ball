#ifndef ROLL_A_BALL_INCLUDE_TEXTUREMANAGER_H_
#define ROLL_A_BALL_INCLUDE_TEXTUREMANAGER_H_
#include "Config.h"

class TextureManager
{
public:
    static TextureManager& Instance();
    void LoadTexture(const std::string& textureName);
    TexturePtr GetTexture(const std::string& textureName);
    void Clear();

private:
    TextureManager() = default;
    ~TextureManager() = default;
    TextureManager(const TextureManager&) = delete;
    TextureManager operator= (const TextureManager&) = delete;

private:
    std::unordered_map<std::string, TexturePtr> m_Textures;
};

#endif //!ROLL_A_BALL_INCLUDE_TEXTUREMANAGER_H_