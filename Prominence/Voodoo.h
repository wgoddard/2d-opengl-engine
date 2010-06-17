#pragma once

#include "PlayerCharacter.h"

namespace Prominence {

	class DECLSPEC Voodoo :
		public PlayerCharacter
	{
	public:
		Voodoo(AnimatedSprite & sprite, b2Body & body, InputDevice &device);
		~Voodoo(void);
	};

}
