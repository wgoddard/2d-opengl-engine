#pragma once

#include "Actor.h"

namespace Prominence {

	class DECLSPEC Monster :
		public Actor
	{
	public:
		Monster(AnimatedSprite & sprite, b2Body & body);
		virtual ~Monster(void);
	};

}
