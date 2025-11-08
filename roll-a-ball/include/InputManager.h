#ifndef ROLL_A_BALL_INCLUDE_INPUTMANAGER_H_
#define ROLL_A_BALL_INCLUDE_INPUTMANAGER_H_
#include "Config.h"

class InputManager
{
private:
    typedef struct Keyboard
    {
        std::unordered_map<int, bool> pressed;
        std::unordered_map<int, bool> trigger;
        std::unordered_map<int, bool> released;
        std::unordered_map<int, bool> previous;
    } Keyboard;

    typedef struct Mouse
    {
        std::unordered_map<int, bool> pressed;
        std::unordered_map<int, bool> trigger;
        std::unordered_map<int, bool> released;
        std::unordered_map<int, bool> previous;

        glm::vec2 currPoint;
        glm::vec2 deltaPoint;
    } Mouse;

    typedef struct Gamepad
    {
        bool isEnable = false;
        std::unordered_map<int, bool> pressed;
        std::unordered_map<int, bool> trigger;
        std::unordered_map<int, bool> released;
        std::unordered_map<int, bool> previous;

        glm::vec2 leftStick;
        glm::vec2 rightStick;
    } Gamepad;

public:
    static InputManager& Instance();

    bool GetKey(int code);
    bool GetMouse(int code);
    glm::vec2 GetMouse();

private:
    void update();
    void reset();
    void setKey(int code, bool press);
    void setMouse(int code, bool press);
    void setMouse(float x, float y);
    
private:
    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager operator= (const InputManager&) = delete;

private:
    Keyboard m_Keyboard;
    Mouse m_Mouse;

private:
    friend class Application;
};

#endif //!ROLL_A_BALL_INCLUDE_INPUTMANAGER_H_