#pragma once

#include "InputDevice.h"
#include "SDL.h"

namespace Prominence {

	class KeyboardController :
		public InputDevice
	{
	protected:
		Uint8* keys;
	public:
		KeyboardController(void);
		virtual ~KeyboardController(void);

		virtual bool GetAKey() = 0;
		virtual bool GetBKey() = 0;
		virtual bool GeyXKey() = 0;
		virtual bool GetYKey() = 0;
		virtual void GetDirection(int &MagX, int &MagY) = 0;
		virtual bool GetLKey() = 0;
		virtual bool GetRKey() = 0;
		virtual bool GetStart() = 0;
	};

}