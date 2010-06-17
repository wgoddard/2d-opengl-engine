#pragma once

#include "InputDevice.h"

namespace Prominence {

	class KeyboardController :
		public InputDevice
	{
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