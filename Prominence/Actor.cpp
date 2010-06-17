#include "Actor.h"

namespace Prominence {

	Actor::Actor(AnimatedSprite & sprite, b2Body & body) : AnimatedEntity(sprite), m_Body(body)
	{
		m_Body.SetUserData(this);
	}

	Actor::~Actor(void)
	{
	}

	void Actor::Update(Uint32 dt)
	{
		AnimatedEntity::Update(dt);

		m_Body.SetLinearVelocity(b2Vec2(0,0));


		//m_XV = 0.1;
		//m_Body.ApplyForce(b2Vec2(1000.0f, 1000.0f), b2Vec2(10.0f,10.0f));
		m_Body.WakeUp();
		//m_Body.SetLinearVelocity(b2Vec2(100.0f,0.0f));
		m_Body.ApplyImpulse(b2Vec2(m_MagX/100, m_MagY/100), m_Body.GetWorldCenter());
		//m_Body.ApplyForce(b2Vec2(3000000000.0f, 0.0), m_Body.GetWorldCenter());
		//m_Animator->Animate("Running");
		m_HFlip = false;
	}

	void Actor::Render()
	{
		b2Vec2 pos = m_Body.GetPosition();
		m_Animator->Render(pos.x * PPU, pos.y * PPU, m_HFlip);
	}

	void Actor::UpdateState()
	{

	}



}