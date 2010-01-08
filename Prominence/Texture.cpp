#include "Texture.h"

namespace Prominence {

	SDL_mutex  *lock;

	Texture::Texture(std::string name, GLuint id)
	{
		Name = name;
		Id = id;
	}

	Texture::~Texture(void)
	{
	}

	GLuint Texture::GetId()
	{
		//SDL_mutexP(lock);
		return Id;
		//SDL_mutexV(lock);
	}

	void Texture::SetId(GLuint id)
	{ 
		//SDL_mutexP(lock);
		Id = id;
		//SDL_mutexV(lock);
	} 

}