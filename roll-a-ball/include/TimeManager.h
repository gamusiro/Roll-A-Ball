#ifndef ROLL_A_BALL_INCLUDE_TIME_MANAGER_H_
#define ROLL_A_BALL_INCLUDE_TIME_MANAGER_H_
#include "Config.h"

class TimeManager
{
public:
    static TimeManager& Instance();

public:
    float GetDeltaTime() const;

private:
    void update();

private:
    std::chrono::steady_clock::time_point m_PrevTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> m_DeltaTime;

private:
    friend class Application;
};

#endif //! ROLL_A_BALL_INCLUDE_TIME_MANAGER_H_