#pragma once

#include "Export.h"
#include "XInputController.h"
//#include "KeyboardController.h"
#include "KeyboardA.h"
#include "KeyboardB.h"
#include "Logger.h"
//#include "PlayerCharacter.h"
#include <vector>

#include <iostream>

namespace Prominence {

	const int MAX_PLAYERS = 4;

	class DECLSPEC InputHandler
	{
	private:
		Logger &m_Logger;
		void FreeHandle(InputDevice &InputDevice);
		//Free Controller Handles
		std::vector<InputDevice *> FreeControllers;
		//Used Controller Handles
		std::vector<InputDevice *> UsedControllers;
	public:
		InputHandler(Logger &logger);
		~InputHandler(void);

		void Poll();
		InputDevice * NewPlayer();
		//void Yo() { std::cout << "sup"; }
	};

}