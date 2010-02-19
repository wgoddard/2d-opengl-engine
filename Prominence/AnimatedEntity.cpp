#include "AnimatedEntity.h"

namespace Prominence {

	AnimatedEntity::AnimatedEntity(AnimatedSprite & sprite, float x, float y) : Entity(sprite, x, y)
	{
		m_Animator = new Animator(sprite);
	}

	AnimatedEntity::~AnimatedEntity(void)
	{
		delete m_Animator;
	}

	void AnimatedEntity::Update(Uint32 dt)
	{
			m_Animator->Update(dt);
			if (m_Animator->LoopFinished())
				m_Animator->Animate("Still");
	}

	void AnimatedEntity::Render()
	{
		m_Animator->Render(m_X, m_Y, m_HFlip);
	}

}