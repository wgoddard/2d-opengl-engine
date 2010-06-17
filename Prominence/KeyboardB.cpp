#include "KeyboardB.h"

namespace Prominence {

	KeyboardB::KeyboardB(void)
	{
	}

	KeyboardB::~KeyboardB(void)
	{
	}

	bool KeyboardB::GetAKey()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_a] ) { return true; }
		return false;

	}

	bool KeyboardB::GetBKey()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_s] ) { return true; }
		return false;
	}

	bool KeyboardB::GeyXKey()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_z] ) { return true; }
		return false;
	}

	bool KeyboardB::GetYKey()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_x] ) { return true; }
		return false;
	}

	void KeyboardB::GetDirection(int &MagX, int &MagY)
	{
		keys = SDL_GetKeyState(NULL);
		MagX = 0;
		MagY = 0;
		if ( keys[SDLK_d] ) MagX += 300;
		if ( keys[SDLK_a] ) MagX -= 300;
		if ( keys[SDLK_w] ) MagY += 300;
		if (keys[SDLK_s] ) MagY -= 300;
	}

	bool KeyboardB::GetLKey()
	{
		return false;
	}

	bool KeyboardB::GetRKey()
	{
		return false;
	}

	bool KeyboardB::GetStart()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_z] ) { return true; }
		return false;
	}

}