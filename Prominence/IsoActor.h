#pragma once
#include "Actor.h"

namespace Prominence {

	enum Direction { N, NE, E, SE, S, SW, W, NW };
	const std::string directions[] = { "N-", "NE-", "E-", "SE-", "S-", "SW-", "W-", "NW-" };

	class DECLSPEC IsoActor :
		public Actor
	{
	private:
		float m_Angle;
		Direction m_Direction;
	protected:
		void UpdateState();
	public:
		IsoActor(AnimatedSprite & sprite, b2Body & body);
		~IsoActor(void);
		void Render();
		void SetAngle(float angle);

	};

}