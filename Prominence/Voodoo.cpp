#include "Voodoo.h"

namespace Prominence {

	Voodoo::Voodoo(AnimatedSprite & sprite, b2Body & body, InputDevice &device) : PlayerCharacter(sprite, body, device)
	{
	}

	Voodoo::~Voodoo(void)
	{
	}

}