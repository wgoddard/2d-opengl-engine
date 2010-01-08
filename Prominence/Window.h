#pragma once

#include "Export.h"
#include "Logger.h"

#include "SDL.h"
#include "SDL_opengl.h"

#include <string>
#include <iostream>

namespace Prominence {

class DECLSPEC Window
{
private:
	std::string m_Title;
	SDL_Surface * m_Screen;
	Uint32 m_Width;
	Uint32 m_Height;
	Uint16 m_Bpp;
	//bool m_Fullscreen;
	Uint32 m_Flags;
	Logger & m_Logger;
public:
	Window(Logger & logger, Uint32 width, Uint32 height, Uint16 bpp, std::string name);
	~Window(void);
	int Start(); 
	int ToggleFullscreen(void);
	void SetTitle(std::string title) { m_Title = title;  SDL_WM_SetCaption(m_Title.c_str(), m_Title.c_str()); }
	int ResizeWindow(Uint32 width, Uint32 height, Uint16 bpp, bool fullscreen);
};

} //Exit Prominence namespace