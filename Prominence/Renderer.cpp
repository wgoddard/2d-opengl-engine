#include "Renderer.h"

namespace Prominence {


	Renderer::Renderer(Logger & logger) : m_Logger(logger)
	{
		m_Logger.Outputf(P_INFO, VIDEO, "Renderer instantiated.\n");
	}

	Renderer::~Renderer(void)
	{
		m_Logger.Outputf(P_INFO, VIDEO, "Renderer destroyed.\n");
	}

	int Renderer::Initialize()
	{
		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8);
		//SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); 


		glEnable(GL_TEXTURE_2D);
		 
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		
		glClear(GL_COLOR_BUFFER_BIT);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		//glDisable(GL_COLOR_MATERIAL);


		GLenum error = glGetError();
		if( error != GL_NO_ERROR ) 
		{
			m_Logger.Outputf(P_ERROR, VIDEO, "Critical error initializing OpenGL: %s.\n", gluErrorString(error));
			exit(1);
		}

		m_Logger.Outputf(P_INFO, VIDEO, "Renderer initialized.\n");
		m_Logger.Outputf(P_INFO, VIDEO, "OpenGL version %s\n", glGetString(GL_VERSION));
		m_Logger.Outputf(P_INFO, VIDEO, "OpenGL vendor: %s\n", glGetString(GL_VENDOR));
		m_Logger.Outputf(P_INFO, VIDEO, "Glu Version: %s\n", gluGetString(GLU_VERSION));
		return 0;
	}

	void Renderer::SetOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
	{
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		 
		glOrtho(left, right, bottom, top, -1.0f, 1.0f);

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

	}

	void Renderer::SetViewPort(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		glViewport(x, y, width, height);
	}

	void Renderer::AddQuad(GLuint texture, const Quad quad)
	{
		std::deque<QuadList>::iterator i;
		//std::deque<Quad>::iterator j;

		for (i = QuadLists.begin(); i != QuadLists.end(); ++i)
		{
			if (i->texture == texture)
			{
				i->Quads.push_back(quad);
				return;
			}
		}

		QuadList ql;
		ql.texture = texture;
		ql.Quads.push_back(quad);

		QuadLists.push_back(ql);

	}

	void Renderer::StartFrame()
	{
	}

	void Renderer::RenderQuads()
	{
			std::deque<QuadList>::iterator i;
			std::deque<Quad>::iterator j;

			for (i = QuadLists.begin(); i != QuadLists.end(); ++i)
			{
				//glPushMatrix();
				//glDisable(GL_BLEND);
				//glEnable(GL_COLOR_MATERIAL);
				glBindTexture(GL_TEXTURE_2D, i->texture);
				glBegin(GL_QUADS);
					for (j = i->Quads.begin(); j != i->Quads.end(); ++j)
					{
						//glColor4f(j->v[0].color[0], j->v[0].color[1], j->v[0].color[2], j->v[0].color[3]);
						glTexCoord2f(j->v[0].tx, j->v[0].ty);
						glVertex3d( j->v[0].x, j->v[2].y,  j->z );

						//glColor4f(j->v[1].color[0], j->v[1].color[1], j->v[1].color[2], j->v[1].color[3]);
						glTexCoord2f(j->v[1].tx, j->v[1].ty);
						glVertex3d( j->v[1].x, j->v[3].y,  j->z );

						//glColor4f(j->v[2].color[0], j->v[2].color[1], j->v[2].color[2], j->v[2].color[3]);
						glTexCoord2f(j->v[2].tx, j->v[2].ty);
						glVertex3d( j->v[2].x, j->v[0].y,  j->z );

						//glColor4f(j->v[3].color[0], j->v[3].color[1], j->v[3].color[2], j->v[3].color[3]);
						glTexCoord2f(j->v[3].tx, j->v[3].ty);
						glVertex3d( j->v[3].x, j->v[1].y,  j->z );
					}
				glEnd();
				//glPopMatrix();
			}

	}

	void Renderer::EndFrame()
	{
		RenderQuads();

		SDL_GL_SwapBuffers();

		QuadLists.clear();
	}

	void Renderer::Test2()
	{
		//GLuint tex_2d = SOIL_load_OGL_texture
		//(
		//	"X.png",
		//	SOIL_LOAD_AUTO,
		//	SOIL_CREATE_NEW_ID,
		//	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		//);
		//GLuint tex_2d = resourceManager.GetTexture("X.png");
		StartFrame();
		ClearFrame();

		Quad quad = {0};
		quad.z = 1;
		quad.v[0].tx = 0; quad.v[0].ty = 1; quad.v[0].x = 0; quad.v[0].y = 0; quad.v[0].color[3] = 0;
		quad.v[1].tx = 1; quad.v[1].ty = 1; quad.v[1].x = 512; quad.v[1].y = 0; quad.v[1].color[3] = 0;
		quad.v[2].tx = 1; quad.v[2].ty = 0; quad.v[2].x = 512; quad.v[2].y = 512; quad.v[2].color[3] = 0;
		quad.v[3].tx = 0; quad.v[3].ty = 0; quad.v[3].x = 0; quad.v[3].y = 512; quad.v[3].color[3] = 0;

		//AddQuad(tex_2d, quad);

		for (int i = 0; i < 4; ++i)
		{
			quad.v[i].x += 200;
			quad.v[i].y += 200;
		}

		quad.v[0].color[2] = 1.0f;
		quad.v[1].color[2] = 1.0f;
		quad.v[2].color[2] = 1.0f;
		quad.v[3].color[2] = 1.0f;

		GLuint tex2 = Load_Title();
		AddQuad(tex2, quad);
		EndFrame();


	}

}




