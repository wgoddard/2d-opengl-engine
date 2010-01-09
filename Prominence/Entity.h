#pragma once

#include "Export.h"
#include "AnimatedSprite.h"

namespace Prominence {

	class DECLSPEC Entity
	{
	private:
		AnimatedSprite & m_Sprite;
		Uint32 m_CurrentSequence;
		Uint32 m_CurrentFrame;
		Uint32 m_FrameTimer;
		Uint32 m_LoopsPlayed;

		GLfloat m_X;
		GLfloat m_Y;

		GLdouble m_XV;
		GLdouble m_YV;

		bool m_Right;
		bool m_Left;

		bool m_Skidding;
		Uint32 m_SkiddingTimer;

		bool m_HFlip;

		Uint32 m_RightTimer;
		Uint16 m_RightCounter;

		void UpdateState();



		void Animate(std::string sequence_name);
	public:
		Entity(AnimatedSprite & sprite);
		virtual ~Entity();
		void Update(Uint32 dt);
		void Render();

		void Right(bool key);
		void Left(bool key);
	};

}
