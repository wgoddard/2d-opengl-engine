#include "PlayerCharacter.h"

namespace Prominence {

	PlayerCharacter::PlayerCharacter(AnimatedSprite & sprite, b2Body & body, InputDevice &device) 
		: Actor(sprite, body), m_InputDevice(device)
	{
		m_HFlip = true;
		m_Busy = 0;
	}

	PlayerCharacter::~PlayerCharacter(void)
	{
	}

	void PlayerCharacter::Update(Uint32 dt)
	{
		//std::cout << "wooh\n";
		m_InputDevice.GetDirection(m_MagX, m_MagY);
		Actor::Update(dt);
	}

}