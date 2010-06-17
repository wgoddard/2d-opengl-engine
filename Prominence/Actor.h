#pragma once

#include "AnimatedEntity.h"

namespace Prominence {

	class DECLSPEC Actor :
		public AnimatedEntity
	{
	protected:
		virtual void UpdateState();
		int m_MagX;
		int m_MagY;
		b2Body & m_Body;
	public:
		Actor(AnimatedSprite & sprite, b2Body & body);
		~Actor(void);
		b2Vec2 GetPos() { return m_Body.GetPosition(); }
		virtual void Update(Uint32 dt);
		void Render();

	};

}