#pragma once

#include "Export.h"

#include "Window.h"
#include "Logger.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include "AnimatedSprite.h"
#include "SimpleSprite.h"
#include "IsoActor.h"
#include "Entity.h"

#include "World.h"

#include <string>

namespace Prominence {

	enum E_Mode {E_DEBUG, E_RELEASE};

	class DECLSPEC Engine
	{
	private:
		bool m_Initialized;
		static bool m_Instantiated;
		Logger * m_Logger;
		Window * m_Window;
		Renderer * m_Renderer;
		World * m_World;
		ResourceManager * m_ResourceManager;

		std::string m_Name;
		Uint32 m_ScreenWidth; //default values to construc window
		Uint32 m_ScreenHeight;
		Uint16 m_ScreenBpp;
		bool m_Fullscreen;
		E_Mode m_Mode;

		bool (*m_FrameFunc)(void);
		bool (*m_RenderFunc)(void);
		static bool m_DefaultFrame();
		static bool m_DefaultRender();

		Uint32 m_StartTime;
		Uint32 m_DeltaTime;
		Uint32 m_FPS;
		Uint32 m_Frames;
		Uint32 m_FrameTimer;

	public:
		Engine(E_Mode mode);
		virtual ~Engine(void);

		int Initialize();
		void Execute();

		void SetFrameFunc	(bool (*framefunc)())	{ m_FrameFunc = framefunc; }
		void SetRenderFunc	(bool (*renderfunc)())	{ m_RenderFunc = renderfunc; }
		void SetName(std::string name) { m_Name = name;  m_Window->SetTitle(name); };
		int Resize(Uint32 width, Uint32 height, Uint16 bpp = 32, bool fullscreen = true);
		void SetMode(E_Mode mode) { m_Mode = mode; if (mode == E_RELEASE) m_Logger->SetTolerance(WARNING_TOLERANCE); else m_Logger->SetTolerance(FULL_TOLERANCE); }

		Logger & GetLogger()		{ return *m_Logger; }
		Window & GetWindow()	{ return *m_Window; }
		Renderer & GetRenderer()	{ return *m_Renderer;}
		ResourceManager & GetResourceManager() { return *m_ResourceManager; }
		World & GetWorld() { return *m_World; }

		Uint32 GetDelta() { return m_DeltaTime; }
		Uint32 GetFPS() { return m_FPS; }
		void Delay(Uint32 time) { SDL_Delay(time); }

		bool GetKeyDown(unsigned int key) { return (SDL_GetKeyState(NULL)[key]);}
		Uint8* GetKeys() { return SDL_GetKeyState(NULL); }


		AnimatedSprite * CreateSprite(std::string filename) { return new AnimatedSprite(*m_ResourceManager, *m_Renderer, *m_Logger, filename); }
		SimpleSprite * CreateSprite(std::string tex_name, float tex_x, float tex_y, float w, float h, float tex_w, float tex_h)
				{ return new SimpleSprite(*m_ResourceManager, *m_Renderer, tex_name, tex_x, tex_y, w, h, tex_w, tex_h); }
		Entity * CreateEntity(Sprite * sprite, float x, float y);
		IsoActor * CreateIsoActor(AnimatedSprite * sprite, float x, float y);
	};

}