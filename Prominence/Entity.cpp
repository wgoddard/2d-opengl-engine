#include "Entity.h"

namespace Prominence {

	Entity::Entity(AnimatedSprite & sprite, b2Body & body) : m_Sprite(sprite), m_Body(body)
	{
		m_Animator = new Animator(sprite);
		m_Body.SetUserData(this);

		m_GroundedCount = 0;

		m_Right = false;
		m_Left = false;
		m_HFlip = false;
		m_Skidding = false;

		m_RightTimer = m_RightCounter = 0;
	}

	Entity::~Entity(void)
	{
		delete m_Animator;

	}


	void Entity::Update(Uint32 dt)
	{
		//std::cout << m_CurrentSequence->name << " " << m_FrameTimer << '\n';
		m_Animator->Update(dt);

		
		if (m_RightCounter > 0)
			m_RightTimer += dt;
		
		if (m_RightTimer >500)
		{
			m_RightTimer = m_RightCounter = 0;
		}

		if (m_Skidding && m_Animator->Played() > 0)
		{
			m_Skidding = false;
			UpdateState();
		}

		if (m_Animator->LoopFinished())
			m_Animator->Animate("Still");

	}

	void Entity::Render()
	{
		b2Vec2 pos = m_Body.GetPosition();

		m_Animator->Render(pos.x, pos.y, m_HFlip);
	}

	void Entity::Right(bool key)
	{
		m_Right = key;
		if (key)
			m_RightCounter++;
		UpdateState();
	}

	void Entity::Left(bool key)
	{
		m_Left = key;
		UpdateState();
	}

	void Entity::Jump(bool key)
	{
		if (key && m_GroundedCount > 0)
			m_Body.ApplyImpulse(b2Vec2(0.0f, 6.0f), m_Body.GetWorldCenter());
	}

	void Entity::UpdateState()
	{
		if (m_Skidding) return;
		if (m_RightCounter >= 2)
		{
			m_RightTimer = m_RightCounter = 0;
			m_Skidding = true;
			m_HFlip = false;
			m_Animator->Animate("Skidding");
			//m_XV = 0.4;
			//m_Body.SetLinearVelocity(b2Vec2(300.0f, 0.0f));
			m_Body.ApplyImpulse(b2Vec2(6.0f, 0.0f), m_Body.GetWorldCenter());
			//m_Right = false;
			//m_Left = false;
			return;
		}
		if (m_Right && m_Left)
		{
			
		}
		else if (m_Right)
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
			//m_XV = -0.1;
			//m_Body.SetLinearVelocity(b2Vec2(-100.0f, 0.0f));
			m_Body.ApplyImpulse(b2Vec2(-3.0f, 0.0f), m_Body.GetWorldCenter());
			m_Animator->Animate("Running");
			m_HFlip = true;
		}
		else
		{
			m_Animator->Animate("Still");
			//m_XV = 0;
			b2Vec2 vec = m_Body.GetLinearVelocity();
			vec.x = 0.0f;
			m_Body.SetLinearVelocity(vec);
		}
	}

}
