#pragma once

#include "KeyboardController.h"

namespace Prominence {

	class DECLSPEC KeyboardB :
		public KeyboardController
	{
	public:
		KeyboardB(void);
		~KeyboardB(void);
		bool GetAKey();
		bool GetBKey();
		bool GeyXKey();
		bool GetYKey();
		void GetDirection(int &MagX, int &MagY);
		bool GetLKey();
		bool GetRKey();
		bool GetStart();
	};

}
