#pragma once

#include "Sprite.h"

namespace Prominence {

	class DECLSPEC SimpleSprite : public Sprite
	{
	private:
		Quad quad;
		float width, height;
		Texture * texture;
	public:
		SimpleSprite(ResourceManager & rm, Renderer & renderer, std::string tex_name, float tex_x, float tex_y, float w, float h, float tex_w, float tex_h);
		virtual ~SimpleSprite(void);

		void Render(GLfloat x, GLfloat y);
	};

} // Exit Prominence Namespace
