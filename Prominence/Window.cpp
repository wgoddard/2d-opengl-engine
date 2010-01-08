#include "Window.h"

namespace Prominence {

Window::Window(Logger & logger, Uint32 width, Uint32 height, Uint16 bpp, std::string name) : m_Logger(logger)
{
	m_Screen = NULL;
	m_Flags = NULL;
	//m_Fullscreen = false;
	m_Height = height;
	m_Width = width;
	m_Bpp = bpp;
	m_Title = name;
	m_Logger.Outputf(P_INFO, WINDOW, "Window instantiated.\n");
}

Window::~Window(void)
{
	if (m_Screen == NULL)
		SDL_FreeSurface(m_Screen);
	SDL_Quit();
	m_Logger.Outputf(P_INFO, WINDOW, "Window destroyed.\n");
}

int Window::Start()
{

	//Assume OpenGL
	m_Flags |= SDL_OPENGL | SDL_RESIZABLE;

	//if (m_Fullscreen)
	//	m_Flags |= SDL_FULLSCREEN;


	int errors = 0;

	//Start SDL 
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		m_Logger.Outputf(P_ERROR, WINDOW, "Failed to initialize SDL. %s\n", SDL_GetError());
		errors++;
	}

	SDL_WM_SetCaption(m_Title.c_str(), m_Title.c_str());


	if(NULL == (m_Screen = SDL_SetVideoMode(m_Width, m_Height, m_Bpp, m_Flags)))
	{
		errors++;
		m_Logger.Outputf(P_ERROR, WINDOW, "Failed to create window %dx%dx%d\n", m_Width, m_Height, m_Bpp);
	}

	//Resize event, because flag allows window resize
	SDL_Event resizeEvent;
	resizeEvent.type = SDL_VIDEORESIZE;
	resizeEvent.resize.w = m_Width;
	resizeEvent.resize.h = m_Height;
	
	SDL_PushEvent(&resizeEvent);


	if(errors != 0)
	{
		m_Logger.Outputf(P_ERROR, WINDOW, "Fatal error has occured.\n");
	}
	else
		m_Logger.Outputf(P_INFO, WINDOW, "Window has been created successfully.\n");

	return errors;
}

int Window::ToggleFullscreen()
{
	m_Flags ^= SDL_FULLSCREEN;

	if (m_Screen == NULL)
		return 0;

	SDL_Surface * tempscreen = NULL;
	if(NULL == (tempscreen = SDL_SetVideoMode(m_Width, m_Height, m_Bpp, m_Flags)))
	{
		m_Logger.Outputf(P_WARNING, WINDOW, "Failed to toggle fullscreen.\n");
		m_Flags ^= SDL_FULLSCREEN;
		return 1;
	}
	else
	{
		SDL_FreeSurface(m_Screen);
		m_Screen = tempscreen;
		return 0;
	}

	return 0;
}

int Window::ResizeWindow(Uint32 width, Uint32 height, Uint16 bpp, bool fullscreen)
{
	if (m_Screen == NULL)
	{
		m_Width = width;
		m_Height = height;
		m_Bpp = bpp;
		//m_Fullscreen = fullscreen;
		if (fullscreen)
			m_Flags |= SDL_FULLSCREEN;
		else
			m_Flags &= ~(SDL_FULLSCREEN);
		return 0;
	}

	SDL_Surface * tempscreen = NULL;
	Uint32 flags = 0;
	if (fullscreen)
		flags |= SDL_FULLSCREEN;
	if(NULL == (tempscreen = SDL_SetVideoMode(width, height, bpp, flags|m_Flags)))
	{
		m_Logger.Outputf(P_WARNING, WINDOW, "Failed to create window %dx%dx%d\n", width, height, bpp);
		return 1;
	}
	else
	{
		SDL_FreeSurface(m_Screen);
		m_Screen = tempscreen;
		m_Width = width;
		m_Height = height;
		m_Bpp = bpp;
		//m_Fullscreen = fullscreen;
		m_Flags |= SDL_FULLSCREEN;
		if (fullscreen)
			m_Flags |= SDL_FULLSCREEN;
		else
			m_Flags &= ~(SDL_FULLSCREEN);
		m_Logger.Outputf(P_INFO, WINDOW, "Resized window to %dx%dx%d %s.\n",
			width, height, bpp, m_Flags & SDL_FULLSCREEN ? "Fullscreen" : "Windowed");
		return 0;
	}
}

}//Exit Prominence namespace