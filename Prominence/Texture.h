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
		void SetWidth(GLuint width) {m_width = width; }
		void SetHeight(GLuint height) {m_height = height; }
		GLuint GetWidth() const { return m_width; }
		GLuint GetHeight() const { return m_height; }
		void SetId(GLuint id); 
	private:
		GLuint Id;
		GLuint m_width, m_height;
	};

}
