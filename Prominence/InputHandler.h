#pragma once

#include "Export.h"
#include "XInputController.h"
#include "KeyboardController.h"
//#include "PlayerCharacter.h"
#include <vector>

namespace Prominence {

	const int MAX_PLAYERS = 4;

	class DECLSPEC InputHandler
	{
	private:
		void FreeHandle(InputDevice &InputDevice);
		//Free Controller Handles
		//Used Controller Handles
	public:
		InputHandler();
		~InputHandler(void);

		void Poll();
	};

}