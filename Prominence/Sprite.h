#pragma once

#include "Global.h"
#include "Export.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <string>

namespace Prominence {

	class DECLSPEC Sprite
	{
	protected:
		ResourceManager & m_ResourceManager;
		Renderer & m_Renderer;
	public:
		Sprite(ResourceManager & rm, Renderer & renderer);
		virtual ~Sprite();

		//virtual void Render(GLfloat x, GLfloat y) = 0;
		//virtual void Update(Uint32 dt) {}
		virtual void Animate(std::string sequence_name) {}
	};

} // Exit Prominence Namespace
