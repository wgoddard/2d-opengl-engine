#pragma once

#include "InputDevice.h"

namespace Prominence {

	class XInputController :
		public InputDevice
	{
	public:
		XInputController(void);
		~XInputController(void);

		bool GetAKey();
		bool GetBKey();
		bool GeyXKey();
		bool GetYKey();
		void GetDirection(int &MagX, int &MagY);
		bool GetLKey();
		bool GetRKey();
	};

}