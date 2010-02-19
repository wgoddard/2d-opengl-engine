#include "Actor.h"

namespace Prominence {

	Actor::Actor(AnimatedSprite & sprite, b2Body & body) : AnimatedEntity(sprite), m_Body(body)
	{
		m_Left = false;
		m_Right = false;
		m_Up = false;
		m_Down = false;
		m_GroundedCount = 0;
		m_Body.SetUserData(this);
	}

	Actor::~Actor(void)
	{
	}

	void Actor::Update(Uint32 dt)
	{
		AnimatedEntity::Update(dt);
	}

	void Actor::Render()
	{
		b2Vec2 pos = m_Body.GetPosition();
		m_Animator->Render(pos.x * PPU, pos.y * PPU, m_HFlip);
	}

	void Actor::UpdateState()
	{
		if (m_Left) std::cout << "Left\t";
		if (m_Right) std::cout << "Right\t";
		if (m_Up) std::cout << "Up\t";
		if (m_Down) std::cout << "Down\t";
		std::cout << '\n';

		m_Body.SetLinearVelocity(b2Vec2(0,0));


		if (m_Right && !m_Left)
		{
			//m_XV = 0.1;
			//m_Body.ApplyForce(b2Vec2(1000.0f, 1000.0f), b2Vec2(10.0f,10.0f));
			m_Body.WakeUp();
			//m_Body.SetLinearVelocity(b2Vec2(100.0f,0.0f));
			m_Body.ApplyImpulse(b2Vec2(3.0f, 0.0f), m_Body.GetWorldCenter());
			//m_Body.ApplyForce(b2Vec2(3000000000.0f, 0.0), m_Body.GetWorldCenter());
			m_Animator->Animate("Running");
			m_HFlip = false;
		}
		else if (m_Left)
		{
			m_Body.ApplyImpulse(b2Vec2(-3.0f, 0.0f), m_Body.GetWorldCenter());
			m_Animator->Animate("Running");
			m_HFlip = true;
		}
		if (m_Up && !m_Down)
		{
			m_Body.ApplyImpulse(b2Vec2(0.0f, 3.0f), m_Body.GetWorldCenter());
		}
		else if (m_Down)
		{
			m_Body.ApplyImpulse(b2Vec2(0.0f, -3.0f), m_Body.GetWorldCenter());
		}

		if (!(m_Down || m_Up || m_Left || m_Right))
		{
			m_Animator->Animate("Still");
			b2Vec2 vec = m_Body.GetLinearVelocity();
			vec.x = 0.0f;
			m_Body.SetLinearVelocity(vec);
		}
	}

	void Actor::Right(bool key)
	{
		m_Right = key;
		//if (key)
		//	m_RightCounter++;
		UpdateState();
	}

	void Actor::Left(bool key)
	{
		m_Left = key;
		UpdateState();
	}

	void Actor::Up(bool key)
	{
		m_Up = key;
		UpdateState();
	}

	void Actor::Down(bool key)
	{
		m_Down = key;
		UpdateState();
	}

	void Actor::Jump(bool key)
	{
		if (key && m_GroundedCount > 0)
			m_Body.ApplyImpulse(b2Vec2(0.0f, 6.0f), m_Body.GetWorldCenter());
	}


}