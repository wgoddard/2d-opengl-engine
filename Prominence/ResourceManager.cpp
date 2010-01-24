#include "ResourceManager.h"


namespace Prominence {

	extern SDL_mutex  *lock;


	ResourceManager::ResourceManager(Logger & logger) : m_Logger(logger)
	{
		//thread = SDL_CreateThread(doThread, NULL);
		//thread = SDL_CreateMemberThread(this, &ResourceManager::LoadTexture);
		rm = this;
		run_thread = true;
		lock = SDL_CreateMutex();
		lock2 = SDL_CreateMutex();
		thread = SDL_CreateThread(ReadTexture, NULL);
	}

	ResourceManager::~ResourceManager(void)
	{
		std::vector<Texture*>::iterator i = textures.begin();
		int size = textures.size();
		GLuint * disposeList = new GLuint[size];

		int j = 0;
		for (i = textures.begin(); i != textures.end(); ++i, ++j)
		{	
			disposeList[j] = (*i)->GetId();
			delete *i;
		}
		glDeleteTextures(size, disposeList);
		delete [] disposeList;
	}

	Texture * ResourceManager::GetTexture(std::string name)
	{
		std::vector<Texture*>::iterator i;
		//return new GLuint;

		for (i = textures.begin(); i != textures.end(); ++i)
		{
			if (name == (*i)->Name )
				return (*i);
		}
	
		Texture * temp = new Texture(name, 1);

		textures.push_back(temp);
		pending_textures.push_back(textures.size()-1);
		i = textures.end();
		return temp;


	}

	int ResourceManager::ReadTexture(void * data)
	{
		while(run_thread)
		{
			//SDL_Delay(5000);
			//std::cout << "Running thread\n";
			for (unsigned int i = 0; i < rm->pending_textures.size(); ++i)
			{
				int index = rm->pending_textures[i];
				Texture * current = rm->textures[index];
				//std::cout << "Hello texture id " << index << " of " << rm->pending_textures.size() << " with name of " << current->Name << '\n';

				PendingInMemory pend;
				std::ifstream in(current->Name.c_str(), std::ios_base::binary);
				if (in.fail())
				{
					std::cout << "Failed to load " << current->Name << '\n';
					return 1;
				}
				in.seekg(0, std::ios::end);
				int length = in.tellg();
				//std::cout << "File size is " << length << '\n';


				//pend.length = in.tellg();
				pend.index = index;




				char * buf = new char[length];
				in.seekg(0);
				in.read(buf, length);

				int width, height, channels;

				//const unsigned char * const buf2 = buf;

				unsigned char * loaded = SOIL_load_image_from_memory(reinterpret_cast<const unsigned char* const>(buf), length, &width, &height, &channels, 0);

				delete buf;
				in.close();

				/// If non-power of two
				if ( (width & (width-1)) || (height & (height-1)) ) {

					int new_width = 1;
					int new_height = 1;
					while( new_width < width )
					{
						new_width *= 2;
					}
					while( new_height < height )
					{
						new_height *= 2;
					}
					/*	still?	*/
					if( (new_width != width) || (new_height != height) )
					{
						/*	yep, resize	*/
						unsigned char *resampled = (unsigned char*)malloc( channels*new_width*new_height );
						up_scale_image(
								loaded, width, height, channels,
								resampled, new_width, new_height );
						SOIL_free_image_data( loaded );
						loaded = resampled;
						width = new_width;
						height = new_height;
					}  
				}///finish Non power of two conversion

				pend.data = loaded;
				pend.channels = channels;
				pend.height = height;
				pend.width = width;

				//rm->pending_memory.push_back(pend);
				//rm->GetD().push_back(pend);
				rm->PushBack(pend);

				//SDL_Delay(100);

				//SDL_Delay(2000); 

			}
			rm->pending_textures.clear();
			//rm->LoadTextures();
			SDL_Delay(100);
		}
		return 1;
	}

	void ResourceManager::LoadTextures()
	{
		//for (int i = 0; i < pending_memory.size(); ++i)
		//{
		//	GLuint tex = (SOIL_load_OGL_texture_from_memory(reinterpret_cast<const unsigned char * const>(pending_memory[i].buf),
		//		pending_memory[i].length, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT));
		//	delete pending_memory[i].buf;
		//	//std::cout << "Loaded as " << tex << '\n';
		//	 textures[pending_memory[i].index]->SetId(tex);
		//}
		//pending_memory.clear();
		//if (pending_memory.size() == 0) return;
		//if (GetD().size() == 0) return;
		while (Size() != 0) {
////*****************************************
		//int i = 0;
		//PendingInMemory * pending = &pending_memory[0];
		//std::deque<PendingInMemory>::iterator i = pending_memory.begin();
		//	//GLuint tex = (SOIL_load_OGL_texture_from_memory(reinterpret_cast<const unsigned char * const>(pending_memory[i].buf),
		//	//	pending_memory[i].length, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

		//	GLuint tex = SOIL_create_OGL_texture(reinterpret_cast<const unsigned char*>(i->data), i->width, i->height, i->channels, SOIL_CREATE_NEW_ID, 0);
		//	//delete pending->data;
		//	std::cout << "Loaded as " << tex << '\n';
		//	std::cout << "Trying to update index " << i->index << " with old value of " << textures[i->index]->GetId() << '\n';
		//	std::cout << "There are " << textures.size() << " textures\n";
		//	std::vector<Texture*>::iterator j = textures.begin() + i->index;
		//	 //textures[(i->index)]->SetId(tex);
		//	(*j)->GetId();
		//	 pending_memory.erase(pending_memory.begin());
/////******************************
				//for (std::deque<PendingInMemory>::iterator i = pending_memory.begin(); i != pending_memory.end(); ++i)
		//for (std::deque<PendingInMemory>::iterator i = Iterator(); i != Iterator() + Size(); ++i)
			PendingInMemory pending = Pop();
			{
				//GLuint tex = (SOIL_load_OGL_texture_from_memory(reinterpret_cast<const unsigned char * const>(pending_memory[i].buf),
				//	pending_memory[i].length, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

				GLuint tex = SOIL_create_OGL_texture(reinterpret_cast<const unsigned char*>(pending.data), pending.width, pending.height, pending.channels, SOIL_CREATE_NEW_ID, 0);
				//delete pending->data;
				//std::cout << "Loaded as " << tex << '\n';
				//std::cout << "Trying to update index " << pending.index << " with old value of " << textures[pending.index]->GetId() << '\n';
				//std::cout << "There are " << textures.size() << " textures\n";
				std::vector<Texture*>::iterator j = textures.begin() + pending.index;
				(*j)->SetId(tex);
				(*j)->SetWidth(pending.width);
				(*j)->SetHeight(pending.height);
				//delete  pending.data;
				SOIL_free_image_data(pending.data);

			 }

				 
				 //[(i->index)]->SetId(tex);
			//(*j)->GetId();
		}
				//GetD().clear();
		//Clear();

			//pending_memory.erase(pending_memory.begin());

	}

	ResourceManager * ResourceManager::rm;
	SDL_mutex * ResourceManager::lock2;
	bool ResourceManager::run_thread = false;

} //Exit Prominence Namespace

