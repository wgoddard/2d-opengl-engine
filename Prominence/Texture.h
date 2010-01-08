#pragma once

#include "SDL_opengl.h"
#include "SDL_mutex.h"
#include <string>
#include "export.h"

namespace Prominence {

	class Texture {
	public:
		Texture(std::string name, GLuint id = 0);
		~Texture();
		std::string Name;
		GLuint GetId();
		void SetId(GLuint id); 
	private:
		GLuint Id;
	};

}
