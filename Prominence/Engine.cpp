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


		m_ScreenHeight = 600;
		m_ScreenWidth = 800;
		m_ScreenBpp = 32;
		m_Name = "Prominence Engine";

		m_Logger = new Logger(); 	SetMode(mode);
		m_Window = new Window(*m_Logger, m_ScreenWidth, m_ScreenHeight, m_ScreenBpp, m_Name);
		m_Renderer = new Renderer(*m_Logger);
		m_ResourceManager = new ResourceManager(*m_Logger);

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
		
		if (m_Renderer != NULL)
			delete m_Renderer;
		else
			m_Logger->Outputf(P_WARNING, VIDEO, "Engine cannot destroy renderer. It does not exist.\n");

		if (m_Window != NULL)
			delete m_Window;
		else
			m_Logger->Outputf(P_WARNING, WINDOW, "Engine cannot destroy window.  It does not exist.\n");


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
			m_Renderer->SetOrtho(0, m_ScreenWidth, m_ScreenHeight, 0);
			m_Renderer->SetViewPort(0, 0, m_ScreenWidth, m_ScreenHeight);
			//m_Renderer.Test2();
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

		//m_Renderer.Test2(); //display logo
		//SDL_Delay(2000); //display logo

		while (m_FrameFunc() && m_RenderFunc() )
		{
			Uint32 currentTime = SDL_GetTicks();
			m_DeltaTime = currentTime - m_StartTime;
			m_StartTime = currentTime;
			m_Frames++;
			m_ResourceManager->LoadTextures();
			if (currentTime - m_FrameTimer >= 1000)
			{
				m_FrameTimer = currentTime;
				m_FPS = m_Frames;
				m_Frames = 0;
			}
		}
	}

	int Engine::Resize(Uint32 width, Uint32 height, Uint16 bpp, bool fullscreen)
	{
		if (m_Window->ResizeWindow(width, height, bpp, fullscreen))
			return 1;
		m_ScreenWidth = width;
		m_ScreenHeight = height;
		m_ScreenBpp = bpp;
		m_Fullscreen = fullscreen;
		return 0;
	}

	bool Engine::m_DefaultFrame()
	{
		return true;
	}

	bool Engine::m_DefaultRender()
	{
		return true;
	}

	bool Engine::m_Instantiated = false;

}

