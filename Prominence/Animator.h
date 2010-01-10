#pragma once

#include "Export.h"
#include "AnimatedSprite.h"

namespace Prominence {

	class DECLSPEC Animator
	{
	private:
		AnimatedSprite & m_Sprite;
		Uint32 m_CurrentSequence;
		Uint32 m_CurrentFrame;
		Uint32 m_FrameTimer;
		Uint32 m_LoopsPlayed;
	public:
		Animator(AnimatedSprite & sprite);
		~Animator(void);
		void Animate(std::string sequence_name);
		void Update(Uint32 dt);
		void Render(GLfloat x, GLfloat y, bool hflip);
		Uint32 Played() { return m_LoopsPlayed; }
		bool LoopFinished() { return m_LoopsPlayed > 0 && m_Sprite.GetSequence(m_CurrentSequence)->loops == 0; }
		//Frame * GetCurrentFrame() { return m_Sprite.GetSequence(m_CurrentSequence)[m_CurrentFrame]; }
	};

}