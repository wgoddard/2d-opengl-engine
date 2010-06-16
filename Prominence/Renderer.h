#pragma once

#include "Global.h"
#include "Export.h"
#include "Logger.h"
#include "ResourceManager.h"
#include "Texture.h"

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
			std::deque <Quad> StaticQuads;
			//GLuint texture;
			Texture *texture;
			QuadList(Texture *texture_) : texture(texture_) { }
		};
		std::deque <QuadList> QuadLists;
		std::deque <Quad> QuadFrames;

		Uint32 m_Frames;

		void RenderQuads();
		void RenderFrames();
	public:
		Renderer(Logger & logger);
		~Renderer(void);
		int Initialize();
		void SetOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
		void SetViewPort(GLint x, GLint y, GLsizei width, GLsizei height);

		void StartFrame();
		void ViewAt(float x, float y) { glTranslated(x, y, 0); }
		void ClearFrame() { glClear(GL_COLOR_BUFFER_BIT); }
		void ClearFrame(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
			{ glClearColor(red, green, blue, alpha); glClear(GL_COLOR_BUFFER_BIT); }
		void AddQuad(Texture * texture, const Quad quad);
		void AddStaticQuad(Texture * texture, const Quad quad);
		void AddFrame(const Quad quad);
		void EndFrame();
		Uint32 GetFrames() { Uint32 frames = m_Frames; m_Frames = 0; return frames; }

		void Test2();
	};

}