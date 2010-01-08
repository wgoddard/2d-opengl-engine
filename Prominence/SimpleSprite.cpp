#include "SimpleSprite.h"

namespace Prominence {

	SimpleSprite::SimpleSprite(ResourceManager & rm, Renderer & renderer, std::string tex_name, float tex_x, float tex_y, float w, float h, float tex_w, float tex_h) : Sprite(rm, renderer)
	{
		texture = m_ResourceManager.GetTexture(tex_name);
		width = w;
		height = h;

		//quad.v[3].color =
		//quad.v[2].color =
		//quad.v[1].color =
		//quad.v[0].color = 1.0f;

		quad.v[0].tx = tex_x;
		quad.v[1].tx = tex_x + w/tex_w;
		quad.v[2].tx = tex_x + w/tex_w;
		quad.v[3].tx = tex_x;

		quad.v[0].ty = tex_y;
		quad.v[1].ty = tex_y;
		quad.v[2].ty = tex_y + h/tex_h;
		quad.v[3].ty = tex_y + h/tex_h;

		quad.z = 0.5f;
	}

	SimpleSprite::~SimpleSprite(void)
	{
	}

	void SimpleSprite::Render(GLfloat x, GLfloat y)
	{
		quad.v[0].x = x; quad.v[0].y = y;
		//quad.v[0].tx = 0; quad.v[0].ty = 0; quad.v[0].x = 0; quad.v[0].y = 0; quad.v[0].color[3] = 0;
		//quad.v[1].tx = 1; quad.v[1].ty = 0; 
		quad.v[1].x = x+width; quad.v[1].y = y; //quad.v[1].color[3] = 0;
		//quad.v[2].tx = 1; quad.v[2].ty = 1; 
		quad.v[2].x = x+width; quad.v[2].y = y+height;// quad.v[2].color[3] = 0;
		//quad.v[3].tx = 0; quad.v[3].ty = 1; 
		quad.v[3].x = x; quad.v[3].y = y+height; //quad.v[3].color[3] = 0;

		m_Renderer.AddQuad(texture->GetId(), quad);
	}

} // Exit Prominence Namespace