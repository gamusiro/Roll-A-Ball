#include "FontManager.h"

#include "Logger.h"
#include "Font.h"

FontManager& FontManager::Instance()
{
    static FontManager instance;
    return instance;
}

FontPtr FontManager::GetFont(const std::string& name)
{
    return m_Fonts.at(name);
}

bool FontManager::init()
{
    LOG_CORE_INFO("FontManager::init");
    if(FT_Init_FreeType(&m_Library))
    {
        LOG_CORE_ERROR("Failed to initialize freetype");
        return false;
    }
    return true;
}

bool FontManager::load(const std::vector<std::string>& list)
{
    for(auto i : list)
    {
        FontPtr ptr = std::make_shared<Font>();
        if(FT_New_Face(m_Library, std::string(FONTS_PATH + i).c_str(), 0, &ptr->m_Face))
        {
            LOG_CORE_ERROR("Failed to load font: " + i);
            return false;
        }
        LOG_CORE_INFO("Font Loaded: " + i);
        m_Fonts.insert({i.c_str(), ptr});
    }
}

void FontManager::term()
{
    LOG_CORE_INFO("FontManager::term");
    m_Fonts.clear();
    FT_Done_FreeType(m_Library);
}