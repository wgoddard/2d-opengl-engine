#pragma once

#include "KeyboardController.h"

namespace Prominence {

class DECLSPEC KeyboardA :
	public KeyboardController
{
public:
	KeyboardA(void);
	~KeyboardA(void);
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