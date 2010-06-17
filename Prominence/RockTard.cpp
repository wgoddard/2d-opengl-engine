#include "RockTard.h"

namespace Prominence {

	RockTard::RockTard(AnimatedSprite & sprite, b2Body & body, InputDevice &device) : PlayerCharacter(sprite, body, device)
	{
		m_HFlip = true;
	}

	RockTard::~RockTard(void)
	{
	}

	void RockTard::Update(Uint32 dt)
	{
		if (m_InputDevice.GetBKey())
		{
			m_Animator->Animate("Attack");
			m_Busy = 1;
		}
		if (m_Animator->LoopFinished())
		{
			m_Animator->Animate("Idle");
			m_Busy = 0;
		}
		if (m_Busy == 0)
			if (m_MagX != 0)
				m_Animator->Animate("Walk");
			else
				m_Animator->Animate("Idle");
		PlayerCharacter::Update(dt);
	}


}
