#pragma once

#include "Export.h"
#include "AnimatedSprite.h"
#include "Box2d.h"
#include "Animator.h"

namespace Prominence {

	class DECLSPEC Entity
	{
	protected:
		AnimatedSprite & m_Sprite;
		
		bool m_Right;
		bool m_Left;
		bool m_Up;
		bool m_Down;

		//bool m_Skidding;

		bool m_HFlip;

		//Uint32 m_RightTimer;
		//Uint16 m_RightCounter;

		int32 m_GroundedCount;
		
		virtual void UpdateState();
		Animator * m_Animator;
		b2Body & m_Body;
	public:
		Entity(AnimatedSprite & sprite, b2Body & body);
		virtual ~Entity();
		virtual void Update(Uint32 dt);
		virtual void Render();

		void Right(bool key);
		void Left(bool key);
		void Up(bool key);
		void Down(bool key);
		void Jump(bool key);

		b2Vec2 GetPos() { return m_Body.GetPosition(); }

		void TouchGround() { ++m_GroundedCount;}
		void UntouchGround() { --m_GroundedCount; }
	};

}
