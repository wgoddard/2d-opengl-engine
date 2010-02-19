#include "IsoEntity.h"

namespace Prominence {

	IsoEntity::IsoEntity(AnimatedSprite & sprite, b2Body & body) : Entity(sprite, body)
	{
	}

	IsoEntity::~IsoEntity(void)
	{
	}

	void IsoEntity::Render()
	{
		b2Vec2 pos = m_Body.GetPosition();

		m_Animator->Render(pos.x, pos.y, false);
	}

	void IsoEntity::SetAngle(float angle)
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

		UpdateState();
		//m_Animator->Animate(directions[m_Direction] + std::string("Walking"));
	}

	void IsoEntity::UpdateState()
	{
		if (m_Left) std::cout << "Left\t";
		if (m_Right) std::cout << "Right\t";
		if (m_Up) std::cout << "Up\t";
		if (m_Down) std::cout << "Down\t";
		std::cout << '\n';

		m_Body.SetLinearVelocity(b2Vec2(0,0));

		std::string state;

		if (m_Right && !m_Left)
		{

			m_Body.ApplyImpulse(b2Vec2(3.0f, 0.0f), m_Body.GetWorldCenter());
			state = "Walking";
			m_HFlip = false;
		}
		else if (m_Left)
		{
			//m_XV = -0.1;
			//m_Body.SetLinearVelocity(b2Vec2(-100.0f, 0.0f));
			m_Body.ApplyImpulse(b2Vec2(-3.0f, 0.0f), m_Body.GetWorldCenter());
			state = "Walking";
			m_HFlip = true;
		}
		if (m_Up && !m_Down)
		{
			m_Body.ApplyImpulse(b2Vec2(0.0f, 3.0f), m_Body.GetWorldCenter());
			state = "Walking";
		}
		else if (m_Down)
		{
			m_Body.ApplyImpulse(b2Vec2(0.0f, -3.0f), m_Body.GetWorldCenter());
			state = "Walking";
		}

		if (!(m_Down || m_Up || m_Left || m_Right))
		{
			//m_Animator->Animate("Still");
			state = "Paused";
			//m_XV = 0;
			b2Vec2 vec = m_Body.GetLinearVelocity();
			vec.x = 0.0f;
			m_Body.SetLinearVelocity(vec);
		}
		m_Animator->Animate(directions[m_Direction] + state);
	}

}