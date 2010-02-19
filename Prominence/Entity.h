#pragma once

#include "Export.h"
#include "Sprite.h"
#include "Box2d.h"

namespace Prominence {

	class DECLSPEC Entity
	{
	protected:
		Sprite & m_Sprite;
		bool m_HFlip;		
		float m_X;
		float m_Y;
	public:
		Entity(Sprite & sprite, float x = 0, float y = 0);
		virtual ~Entity();
		virtual void Update(Uint32 dt) {}
		virtual void Render();
		virtual b2Vec2 GetPos() { return b2Vec2(m_X, m_Y); }

	};

}
