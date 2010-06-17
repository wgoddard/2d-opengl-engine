#include "KeyboardA.h"

namespace Prominence {


	KeyboardA::KeyboardA(void)
	{
	}

	KeyboardA::~KeyboardA(void)
	{
	}

	bool KeyboardA::GetAKey()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_a] ) { return true; }
		return false;

	}

	bool KeyboardA::GetBKey()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_s] ) { return true; }
		return false;
	}

	bool KeyboardA::GeyXKey()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_z] ) { return true; }
		return false;
	}

	bool KeyboardA::GetYKey()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_x] ) { return true; }
		return false;
	}

	void KeyboardA::GetDirection(int &MagX, int &MagY)
	{
		keys = SDL_GetKeyState(NULL);
		MagX = 0;
		MagY = 0;
		if ( keys[SDLK_RIGHT] ) MagX += 300;
		if ( keys[SDLK_LEFT] ) MagX -= 300;
		if ( keys[SDLK_UP] ) MagY += 300;
		if (keys[SDLK_DOWN] ) MagY -= 300;
	}

	bool KeyboardA::GetLKey()
	{
		return false;
	}

	bool KeyboardA::GetRKey()
	{
		return false;
	}

	bool KeyboardA::GetStart()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_RETURN] ) { return true; }
		return false;
	}

}