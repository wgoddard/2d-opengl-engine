#pragma once
#include "Entity.h"
#include "Animator.h"

namespace Prominence {

	class DECLSPEC AnimatedEntity :
		public Entity
	{
	protected:
		Animator * m_Animator;
	public:
		AnimatedEntity(AnimatedSprite & sprite, float x = 0, float y = 0);
		~AnimatedEntity(void);
		virtual void Update(Uint32 dt);
		virtual void Render();
	};

}