#pragma once

#include "Export.h"
#include "AnimatedSprite.h"
#include "Box2d.h"
#include "Animator.h"

namespace Prominence {

	class DECLSPEC Entity
	{
	private:
		AnimatedSprite & m_Sprite;
		Animator * m_Animator;
		b2Body & m_Body;


		bool m_Right;
		bool m_Left;

		bool m_Skidding;

		bool m_HFlip;

		Uint32 m_RightTimer;
		Uint16 m_RightCounter;

		void UpdateState();

	public:
		Entity(AnimatedSprite & sprite, b2Body & body);
		virtual ~Entity();
		void Update(Uint32 dt);
		void Render();

		void Right(bool key);
		void Left(bool key);
	};

}
