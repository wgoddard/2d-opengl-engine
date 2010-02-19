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
		int32 id = m_Sprite.GetSequence(sequence_name);


		if (id == -1 || id == m_CurrentSequence)
			return;


		m_CurrentSequence = id;
		m_CurrentFrame = 0;
		m_FrameTimer = 0;
		m_LoopsPlayed = 0;

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