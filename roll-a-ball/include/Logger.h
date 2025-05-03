#ifndef ROLL_A_BALL_INCLUDE_LOGGER_H_
#define ROLL_A_BALL_INCLUDE_LOGGER_H_
#include "Config.h"

class Logger
{
public:
    static Logger& Instance();
    inline std::shared_ptr<spdlog::logger> GetCore() { return m_Core; }

private:
    void init();
    void term();

private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger operator= (const Logger&) = delete;

private:
    std::shared_ptr<spdlog::logger> m_Core;
    friend class Application;
};

#define LOG_CORE_ERROR(...) Logger::Instance().GetCore()->error(__VA_ARGS__)
#define LOG_CORE_WARN(...)  Logger::Instance().GetCore()->warn(__VA_ARGS__)
#define LOG_CORE_INFO(...)  Logger::Instance().GetCore()->info(__VA_ARGS__)
#define LOG_CORE_TRACE(...) Logger::Instance().GetCore()->trace(__VA_ARGS__)
#define LOG_CORE_FATAL(...) Logger::Instance().GetCore()->fatal(__VA_ARGS__)

#endif //!ROLL_A_BALL_INCLUDE_LOGGER_H_