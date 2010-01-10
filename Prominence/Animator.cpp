#include "Animator.h"

namespace Prominence {

	Animator::Animator(AnimatedSprite & sprite) : m_Sprite(sprite)
	{
		m_CurrentSequence = 0;
		m_CurrentFrame = 0;
		m_FrameTimer = 0;
		m_LoopsPlayed = 0;
	}

	Animator::~Animator(void)
	{
	}

	void Animator::Animate(std::string sequence_name)
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

	void Animator::Update(Uint32 dt)
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
	}

	void Animator::Render(GLfloat x, GLfloat y, bool hflip)
	{
		m_Sprite.Render(x, y, m_CurrentSequence, m_CurrentFrame, hflip);
	}

}