#ifndef ROLL_A_BALL_INCLUDE_KEYEVENT_H_
#define ROLL_A_BALL_INCLUDE_KEYEVENT_H_

class KeyEvent
{
protected:
	KeyEvent(int keyCode)
		:m_KeyCode(keyCode) {}

public:
	inline int GetKeyCode() const { return m_KeyCode; }

private:
	int m_KeyCode;
};

class KeyEventPressed final : public KeyEvent
{
public:
    KeyEventPressed(int keyCode, int repeat)
		:KeyEvent(keyCode), m_Repeat(repeat){}

	inline int GetRepeat() const { return m_Repeat; }

private:
	int m_Repeat;
};

class KeyEventReleased final : public KeyEvent
{
public:
    KeyEventReleased(int keyCode)
		:KeyEvent(keyCode){}
};

#endif //!ROLL_A_BALL_INCLUDE_KEYEVENT_H_