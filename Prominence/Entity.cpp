#include "Entity.h"

namespace Prominence {

	Entity::Entity(AnimatedSprite & sprite, b2Body & body) : m_Sprite(sprite), m_Body(body)
	{
		m_CurrentSequence = 0;
		m_CurrentFrame = 0;
		m_FrameTimer = 0;
		m_LoopsPlayed = 0;

		m_X = 100;
		m_Y = 100;
		m_XV = 0;
		m_YV = 0;
		m_Right = false;
		m_Left = false;
		m_HFlip = false;
		m_Skidding = false;

		m_RightTimer = m_RightCounter = 0;
		m_SkiddingTimer = 0;
	}

	Entity::~Entity(void)
	{
	}

	void Entity::Animate(std::string sequence_name)
	{
		if (sequence_name == m_Sprite.GetSequence(m_CurrentSequence)->name)
			return;

		//std::vector<Sequence *>::iterator i;
		
		for (unsigned int i = 0; i < m_Sprite.GetSequenceCount(); ++i)
		{
			if (m_Sprite.GetSequence(i)->name == sequence_name)
			{
				m_CurrentSequence = i;
				m_CurrentFrame = 0;
				m_FrameTimer = 0;
				m_LoopsPlayed = 0;
				return;
			}
		}
	}

	void Entity::Update(Uint32 dt)
	{
		m_FrameTimer += dt;
		Frame * currentFrame = m_Sprite.GetSequence(m_CurrentSequence)->frames[m_CurrentFrame];

		int loops = m_Sprite.GetSequence(m_CurrentSequence)->loops;

		if (loops > 0 || m_LoopsPlayed == 0)
		{
			if (m_FrameTimer > currentFrame->time * 1000)
			{
				m_FrameTimer -= currentFrame->time * 1000;
				m_CurrentFrame++;
				if (m_CurrentFrame >= m_Sprite.GetSequence(m_CurrentSequence)->frames.size()) 
				{
					m_CurrentFrame = m_Sprite.GetSequence(m_CurrentSequence)->returnLoopFrame;
					m_LoopsPlayed++;
				}
			}
		}
		//std::cout << m_CurrentSequence->name << " " << m_FrameTimer << '\n';

		
		if (m_RightCounter > 0)
			m_RightTimer += dt;
		
		if (m_RightTimer >500)
		{
			m_RightTimer = m_RightCounter = 0;
		}

		if (m_Skidding && m_LoopsPlayed > 0)
		{
			m_Skidding = false;
			m_SkiddingTimer = 0;
			m_XV = 0;
			UpdateState();
		}

		if (m_Skidding) m_XV *= 0.98;

		m_X += m_XV * dt;
	}

	void Entity::Render()
	{
		b2Vec2 pos = m_Body.GetPosition();

		m_Sprite.Render(pos.x, pos.y, m_CurrentSequence, m_CurrentFrame, m_HFlip);
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

	void Entity::UpdateState()
	{
		if (m_Skidding) return;
		if (m_RightCounter >= 2)
		{
			m_RightTimer = m_RightCounter = 0;
			m_Skidding = true;
			m_HFlip = false;
			Animate("Skidding");
			//m_XV = 0.4;
			m_Body.SetLinearVelocity(b2Vec2(300.0f, 0.0f));
			//m_Right = false;
			//m_Left = false;
			return;
		}
		if (m_Right && m_Left)
		{
			m_XV = 0;
		}
		else if (m_Right)
		{
			//m_XV = 0.1;
			//m_Body.ApplyForce(b2Vec2(1000.0f, 1000.0f), b2Vec2(10.0f,10.0f));
			m_Body.WakeUp();
			m_Body.SetLinearVelocity(b2Vec2(100.0f,0.0f));
			Animate("Running");
			m_HFlip = false;
		}
		else if (m_Left)
		{
			//m_XV = -0.1;
			m_Body.SetLinearVelocity(b2Vec2(-100.0f, 0.0f));
			Animate("Running");
			m_HFlip = true;
		}
		else
		{
			Animate("Still");
			//m_XV = 0;
			m_Body.SetLinearVelocity(b2Vec2(0.0f,0.0f));
		}
	}

}
