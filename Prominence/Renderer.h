#pragma once

#include "Global.h"
#include "Export.h"
#include "Logger.h"
#include "ResourceManager.h"

#include "SDL.h"
#include "SDL_opengl.h"

#include <deque>



//#include "SOIL.h"

namespace Prominence {

	class DECLSPEC Renderer
	{
	private:
		Logger & m_Logger;

		//Batch rendering by textures
		//Possible Z Buffer sorting within texture batch
		//   or possibly ignore texture batching in favour of Z
		//   because Z buffering no likey blend
		//Switch to pointers to Quad/QuadList
		struct QuadList
		{
			std::deque <Quad> Quads;
			GLuint texture;
		};
		std::deque <QuadList> QuadLists;

		void RenderQuads();
	public:
		Renderer(Logger & logger);
		~Renderer(void);
		int Initialize();
		void SetOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
		void SetViewPort(GLint x, GLint y, GLsizei width, GLsizei height);

		void StartFrame();
		void ClearFrame() { glClear(GL_COLOR_BUFFER_BIT); }
		void ClearFrame(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
			{ glClearColor(red, green, blue, alpha); glClear(GL_COLOR_BUFFER_BIT); }
		void AddQuad(GLuint texture, const Quad quad);
		void EndFrame();

		void Test2();
	};

}