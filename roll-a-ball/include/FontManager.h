#ifndef ROLL_A_BALL_INCLUDE_FONTMANAGER_H_
#define ROLL_A_BALL_INCLUDE_FONTMANAGER_H_
#include "Config.h"


class FontManager
{
public:
    static FontManager& Instance();
    FontPtr GetFont(const std::string& name);

private:
    bool init();
    bool load(const std::vector<std::string>& list);
    void term();

private:
    FontManager() = default;
    ~FontManager() = default;
    FontManager(const FontManager&) = delete;
    FontManager operator= (const FontManager&) = delete;

private:
    FT_Library m_Library;
    std::unordered_map<std::string, FontPtr> m_Fonts;

private:
    friend class Application;
};

#endif //!ROLL_A_BALL_INCLUDE_FONTMANAGER_H_