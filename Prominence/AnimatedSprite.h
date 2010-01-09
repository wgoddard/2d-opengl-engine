#pragma once
#include "Sprite.h"
#include "tinyxml.h"
#include "Logger.h"

namespace Prominence {

	struct Frame
	{
		Quad quad;
		float time;
		Texture * texture;
		int width;
		int height;
		float xAnchor;
		float yAnchor;
	};

	struct Sequence
	{
		std::string name;
		std::vector<Frame *> frames;
		int returnLoopFrame;
		int loops;
	};
	
	class DECLSPEC AnimatedSprite : Sprite
	{

		private:
			std::vector<Sequence *> sequences;
			Logger & m_Logger;
		public:
			AnimatedSprite(ResourceManager & rm, Renderer & renderer, Logger & logger, std::string xml_file);
			virtual ~AnimatedSprite(void);
			void Render(GLfloat x, GLfloat y, Uint32 sequence, Uint32 frame, bool hflip = false);
			Sequence * GetSequence(Uint32 sequence) { return sequences[sequence]; }
			unsigned int GetSequenceCount() { return sequences.size(); }
	};


}