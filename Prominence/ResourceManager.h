#pragma once

#include <string>
#include <vector>
#include <deque>

#include "Export.h"

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_thread.h"
#include "SDL_mutex.h"
#include "SOIL.h"
#include "image_helper.h"
#include "Logger.h"
#include "Global.h"

#include <fstream>

#include <iostream>

namespace Prominence {



class DECLSPEC ResourceManager
{
	struct PendingInMemory {
		unsigned char * data;
		//int length;
		int width;
		int height;
		int channels;
		int index;
	};

	class DECLSPEC Wrapper
	{
	public:
		Wrapper(SDL_mutex * m) : mu(m) { SDL_mutexP(m); }
		~Wrapper() { SDL_mutexV(mu); }
	private:
		SDL_mutex * mu;

	};

private:
	std::vector <Texture *> textures;
	std::vector <unsigned int> pending_textures;
	std::deque <PendingInMemory> pending_memory;
	SDL_Thread * thread;
	static int ReadTexture(void * data);
	static ResourceManager * rm;
	static SDL_mutex * lock2;
	Logger & m_Logger;
	static bool run_thread;
public:
	ResourceManager(Logger & logger);
	~ResourceManager(void);

	Texture * GetTexture(std::string name);
	void LoadTextures();

	//std::deque<PendingInMemory> & GetD() { SDL_mutexP(lock2); return pending_memory; }
	void PushBack(PendingInMemory pending) { Wrapper wrapper(lock2); pending_memory.push_back(pending); }
	int Size() { Wrapper wrapper(lock2); return pending_memory.size(); }
	//std::deque<PendingInMemory>::iterator Iterator() { Wrapper wrapper2(lock2); return pending_memory.begin(); }
	PendingInMemory Pop() { Wrapper wrapper2(lock2); PendingInMemory temp = pending_memory[0];  pending_memory.erase(pending_memory.begin()); return temp; }
	//void Clear() {Wrapper wrapper(lock2); pending_memory.clear(); }
};

} //Exit Prominence Namespace