#ifndef ROLL_A_BALL_INCLUDE_APPLICATION_H_
#define ROLL_A_BALL_INCLUDE_APPLICATION_H_
#include "Config.h"

class Application
{
public:
    void Run();

private:
    bool init();
    void term();

private:
    GLFWwindow* m_Window;
};

#endif //!ROLL_A_BALL_INCLUDE_APPLICATION_H_