#include "IsoActor.h"

namespace Prominence {

	IsoActor::IsoActor(AnimatedSprite & sprite, b2Body & body) : Actor(sprite, body)
	{
		m_Direction = E;
	}

	IsoActor::~IsoActor(void)
	{
	}

	void IsoActor::Render()
	{
		b2Vec2 pos = m_Body.GetPosition();

		m_Animator->Render(pos.x * PPU, pos.y * PPU, false);
	}

	void IsoActor::SetAngle(float angle)
	{
		m_Angle = angle;
		//negative is north, positive is south, increases clockwise


		if (angle < 0) //north
		{
			//direction = "N-";
			if (angle > -MATH_PI/4 - MATH_PI/8)
				m_Direction = NE;
			else if (angle > -MATH_PI/4*3)
				m_Direction = N;
			else
				m_Direction = NW;
		}
		else if (angle > 0) //south
		{
			if (angle < MATH_PI/4 + MATH_PI/8)
				m_Direction = SE;
			else if (angle < MATH_PI/4*3)
				m_Direction = S;
			else
				m_Direction = SW;
			//direction = "S-";

		}
		
		if (angle < 0.3 && angle > -0.3)
			m_Direction = E;
		if (angle > MATH_PI-0.3 || angle < -(MATH_PI+0.3))
			m_Direction = W;

		IsoActor::UpdateState();
		//m_Animator->Animate(directions[m_Direction] + std::string("Walking"));
	}

	void IsoActor::UpdateState()
	{
	}

}