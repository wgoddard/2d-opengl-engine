#include "KeyboardController.h"

namespace Prominence {

	KeyboardController::KeyboardController(void)
	{
	}

	KeyboardController::~KeyboardController(void)
	{
	}

	bool KeyboardController::GetAKey()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_a] ) { return true; }
		return false;

	}

	bool KeyboardController::GetBKey()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_s] ) { return true; }
		return false;
	}

	bool KeyboardController::GeyXKey()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_z] ) { return true; }
		return false;
	}

	bool KeyboardController::GetYKey()
	{
		keys = SDL_GetKeyState(NULL);
		if ( keys[SDLK_x] ) { return true; }
		return false;
	}

	void KeyboardController::GetDirection(int &MagX, int &MagY)
	{
		keys = SDL_GetKeyState(NULL);
		MagX = 0;
		MagY = 0;
		if ( keys[SDLK_RIGHT] ) MagX += 300;
		if ( keys[SDLK_LEFT] ) MagX -= 300;
		if ( keys[SDLK_UP] ) MagY += 300;
		if (keys[SDLK_DOWN] ) MagY -= 300;
	}

	bool KeyboardController::GetLKey()
	{
		return false;
	}

	bool KeyboardController::GetRKey()
	{
		return false;
	}

}