#ifndef ROLL_A_BALL_INCLUDE_TEXTURE_H_
#define ROLL_A_BALL_INCLUDE_TEXTURE_H_
#include "Config.h"

class Texture
{
public:
	void Bind();
	void Unbind();

private:
	unsigned int m_ID;
	int m_Width, m_Height;
	int m_Channels;

private:
	friend class TextureManager;
};

#endif //!ROLL_A_BALL_INCLUDE_TEXTURE_H_