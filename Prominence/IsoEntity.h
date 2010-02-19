#pragma once
#include "Entity.h"

namespace Prominence {

	enum Direction { N, NE, E, SE, S, SW, W, NW };
	const std::string directions[] = { "N-", "NE-", "E-", "SE-", "S-", "SW-", "W-", "NW-" };

	class DECLSPEC IsoEntity :
		public Entity
	{
	private:
		float m_Angle;
		Direction m_Direction;
	protected:
		void UpdateState();
	public:
		IsoEntity(AnimatedSprite & sprite, b2Body & body);
		~IsoEntity(void);
		void Render();
		void SetAngle(float angle);

	};

}