#pragma once

#include "AnimatedEntity.h"

namespace Prominence {

	class DECLSPEC Actor :
		public AnimatedEntity
	{
	protected:
		virtual void UpdateState();
		bool m_Right;
		bool m_Left;
		bool m_Up;
		bool m_Down;
		int32 m_GroundedCount;
		b2Body & m_Body;
	public:
		Actor(AnimatedSprite & sprite, b2Body & body);
		~Actor(void);
		b2Vec2 GetPos() { return m_Body.GetPosition(); }
		void Update(Uint32 dt);
		void Render();
		void Right(bool key);
		void Left(bool key);
		void Up(bool key);
		void Down(bool key);
		void Jump(bool key);
		void TouchGround() { ++m_GroundedCount;}
		void UntouchGround() { --m_GroundedCount; }

	};

}