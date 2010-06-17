#include "PlayerCharacter.h"

namespace Prominence {

	PlayerCharacter::PlayerCharacter(AnimatedSprite & sprite, b2Body & body, InputDevice &device) : Actor(sprite, body), m_InputDevice(device)
	{
	}

	PlayerCharacter::~PlayerCharacter(void)
	{
	}

}