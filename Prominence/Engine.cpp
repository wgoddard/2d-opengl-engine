#include "Engine.h"

namespace Prominence {


	Engine::Engine(E_Mode mode)
	{
		if (m_Instantiated == true)
		{
			m_Logger->Outputf(P_WARNING, ENGINE, "Additional instance of engine.  Non fatal, but terminating.\n");
			exit(-1);
		}
		else
			m_Instantiated = true;


		m_Initialized = false;


		m_ScreenHeight = 300;
		m_ScreenWidth = 400;
		m_ScreenBpp = 32;
		m_Name = "Prominence Engine";

		m_Logger = new Logger(); 	SetMode(mode);
		m_Window = new Window(*m_Logger, m_ScreenWidth, m_ScreenHeight, m_ScreenBpp, m_Name);
		m_Renderer = new Renderer(*m_Logger);
		m_ResourceManager = new ResourceManager(*m_Logger);
		m_World = new World(*m_ResourceManager, *m_Logger, *m_Renderer);
		m_InputHandler = new InputHandler(*m_Logger);

		m_FrameFunc = &m_DefaultFrame;
		m_RenderFunc = &m_DefaultRender;

		m_StartTime = 0;
		m_DeltaTime = 0;
		m_FPS = 0;
		m_Frames = 0;
		m_FrameTimer = 0;

		m_Logger->Outputf(P_INFO, ENGINE, "Engine instantiated.\n");
	}

	Engine::~Engine(void)
	{
		delete m_ResourceManager;

		if (m_InputHandler != NULL)
			delete m_InputHandler;
		else
			m_Logger->Outputf(P_WARNING, INPUT, "Failed to shut down input handler.\n");
		
		if (m_Renderer != NULL)
			delete m_Renderer;
		else
			m_Logger->Outputf(P_WARNING, VIDEO, "Engine cannot destroy renderer. It does not exist.\n");

		if (m_Window != NULL)
			delete m_Window;
		else
			m_Logger->Outputf(P_WARNING, WINDOW, "Engine cannot destroy window.  It does not exist.\n");

		delete m_World;



		m_Logger->Outputf(P_INFO, ENGINE, "Engine destroyed.\n");

		delete m_Logger;
	}

	int Engine::Initialize()
	{
		int error = 0;

		if (m_Initialized == false)
		{
			m_Logger->Outputf(P_INFO, ENGINE, "Engine initializing.\n");
		}
		else 
		{
			m_Logger->Outputf(P_WARNING, ENGINE, "Engine already initialized!\n");
			return 1;
		}

		
		error = m_Window->Start();
		if (error)
		{
			m_Logger->Outputf(P_ERROR, ENGINE, "Fatal error has occured.  Exiting.\n");
			exit(error);
		}

		error = m_Renderer->Initialize();
		if (error)
		{
			exit(error);
		}
		else
		{
			m_Initialized = true;
			m_Renderer->SetOrtho(0, m_ScreenWidth, 0, m_ScreenHeight);
			m_Renderer->SetViewPort(0, 0, m_ScreenWidth, m_ScreenHeight);
			//m_Renderer.Test2();
			Load_Title();
		}

		return 0;

	}

	void Engine::Execute()
	{
		if (m_Initialized == false)
		{
			m_Logger->Outputf(P_ERROR, ENGINE, "Engine is not yet initialized.\n");
			return;
		}

		m_Logger->Outputf(P_INFO, ENGINE, "Engine begining loop\n");
		m_FrameTimer = m_StartTime = SDL_GetTicks();

		if (m_FrameFunc == m_DefaultFrame) m_Logger->Outputf(P_WARNING, ENGINE, "No Frame function was defined.\n");
		if (m_RenderFunc == m_DefaultRender) m_Logger->Outputf(P_WARNING, VIDEO, "No Render function was defined.\n");

		//m_Renderer->Test2(); //display logo
		//SDL_Delay(2000); //display logo

		static int totalFrames = 0;
		static int totalTime = SDL_GetTicks();


		while (m_FrameFunc() && m_RenderFunc())
		{
			Uint32 currentTime = SDL_GetTicks();
			m_DeltaTime = currentTime - m_StartTime;
			m_StartTime = currentTime;
			//m_Frames++;
			totalFrames++;
			//m_World->Update(m_DeltaTime);
			m_ResourceManager->LoadTextures();
			//m_InputHandler->Poll();

			if ((currentTime - m_FrameTimer )>= 1000)
			{
				m_FPS = m_Renderer->GetFrames();
				//m_FPS = m_Frames * 1000.0f / (currentTime - m_FrameTimer);
				m_FrameTimer = currentTime;
				m_Frames = 0;
			}
		}

		std::cout << "Total FPS average = " << totalFrames / ((SDL_GetTicks()-totalTime)/1000) << '\n';
	}

	int Engine::Resize(Uint32 width, Uint32 height, Uint16 bpp, bool fullscreen)
	{
		//m_ResourceManager->FlushGLTextures();
		if (m_Window->ResizeWindow(width, height, bpp, fullscreen))
			return 1;
		m_ScreenWidth = width;
		m_ScreenHeight = height;
		m_ScreenBpp = bpp;
		m_Fullscreen = fullscreen;
		//m_Renderer->SetOrtho(0, width, 0, height);
		//m_Renderer->SetViewPort(0, 0, width, height);
		//m_ResourceManager->ReloadGLTextures();
		return 0;
	}

	bool Engine::m_DefaultFrame()
	{
		SDL_Delay(100);
		return true;
	}

	bool Engine::m_DefaultRender()
	{
		return true;
	}

	Entity * Engine::CreateEntity(Sprite * sprite, float x, float y)
	{
		//b2Body * body = m_World->CreateBody(sprite->GetPolyDef(), x, y);
		//return new Entity(*sprite, *body);
		return m_World->CreateEntity(sprite, x, y);
	}

	IsoActor * Engine::CreateIsoActor(AnimatedSprite * sprite, float x, float y)
	{
		b2Body * body = m_World->CreateBody(sprite->GetPolyDef(), x, y);
		return new IsoActor(*sprite, *body);
	}

	InputDevice * Engine::NewPlayer()
	{
		return m_InputHandler->NewPlayer();
		//return NULL;
	}

	//PlayerCharacter * Engine::CreatePlayerCharacter(AnimatedSprite * sprite, float x, float y)
	//{
	//	b2Body * body = m_World->CreateBody(sprite->GetPolyDef(), x, y);
	//	InputDevice * d = new KeyboardController();
	//	return new PlayerCharacter(*sprite, *body, *d);
	//}

	bool Engine::m_Instantiated = false;

}

