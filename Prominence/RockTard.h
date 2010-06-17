#pragma once

#include "PlayerCharacter.h"

namespace Prominence {

	class DECLSPEC RockTard :
		public PlayerCharacter
	{
	public:
		RockTard(AnimatedSprite & sprite, b2Body & body, InputDevice &device);
		~RockTard(void);
		void Update(Uint32 dt);
	};

}
