#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "SDL_opengl.h"
#include "Texture.h"
#include <string>

#define PIXELS_PER_UNIT 44.0f

namespace Prominence {

	GLuint Load_Title();
	
	struct Vertex 
	{
		GLdouble x, y;
		GLfloat color[4];
		GLfloat tx, ty;
	};

	struct Quad
	{
		//GLuint texture;
		Vertex v[4];
		GLdouble z;

		//Blend
	};



}


#endif