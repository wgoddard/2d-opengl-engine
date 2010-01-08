#pragma once
#include "Sprite.h"
#include "tinyxml.h"
#include "Logger.h"

namespace Prominence {
	
	class DECLSPEC AnimatedSprite : Sprite
	{
		struct Frame
		{
			Quad quad;
			float time;
			Texture * texture;
			int width;
			int height;
		};

		struct Sequence
		{
			std::string name;
			std::vector<Frame *> frames;
			int returnLoopFrame;
		};

	private:
		std::vector<Sequence *> sequences;
		Sequence * m_CurrentSequence;
		Uint32 m_CurrentFrame;
		Uint32 m_FrameTimer;
		Logger & m_Logger;
	public:
		AnimatedSprite(ResourceManager & rm, Renderer & renderer, Logger & logger, std::string xml_file);
		virtual ~AnimatedSprite(void);
		void Render(GLfloat x, GLfloat y);
		void Update(Uint32 dt);
		void Animate(std::string sequence_name);
	};


}