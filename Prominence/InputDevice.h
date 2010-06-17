#pragma once

#include "Export.h"

namespace Prominence {

	class DECLSPEC InputDevice
	{
	public:
		InputDevice(void);
		virtual ~InputDevice(void);

		virtual bool GetAKey() = 0;
		virtual bool GetBKey() = 0;
		virtual bool GeyXKey() = 0;
		virtual bool GetYKey() = 0;
		virtual void GetDirection(int &MagX, int &MagY) = 0;
		virtual bool GetLKey() = 0;
		virtual bool GetRKey() = 0;
	};

}