#pragma once

#include "Export.h"
#include "Actor.h"
#include "InputDevice.h"

namespace Prominence {


	class DECLSPEC PlayerCharacter :
		public Actor
	{
	private:
		InputDevice &m_InputDevice;
	public:
		PlayerCharacter(AnimatedSprite & sprite, b2Body & body, InputDevice &device);
		~PlayerCharacter(void);
	};

}