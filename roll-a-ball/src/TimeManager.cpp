#include "TimeManager.h"

TimeManager& TimeManager::Instance()
{
    static TimeManager instance;
    return instance;
}

float TimeManager::GetDeltaTime() const
{
    return m_DeltaTime.count();
}

void TimeManager::update()
{
    auto currentTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> elapsedTime = currentTime - m_PrevTime;
    m_DeltaTime = elapsedTime;
    m_PrevTime = currentTime;
}