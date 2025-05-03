#include "Logger.h"

Logger& Logger::Instance()
{
    static Logger instance;
    return instance;
}

void Logger::init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    m_Core = spdlog::stdout_color_mt("Roll-A-Ball");
    m_Core->set_level(spdlog::level::trace);
}

void Logger::term()
{

}