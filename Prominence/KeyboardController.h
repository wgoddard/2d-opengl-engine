#pragma once

#include "InputDevice.h"
#include "SDL.h"

namespace Prominence {

	class KeyboardController :
		public InputDevice
	{
	private:
		Uint8* keys;
	public:
		KeyboardController(void);
		~KeyboardController(void);

		bool GetAKey();
		bool GetBKey();
		bool GeyXKey();
		bool GetYKey();
		void GetDirection(int &MagX, int &MagY);
		bool GetLKey();
		bool GetRKey();
	};

}