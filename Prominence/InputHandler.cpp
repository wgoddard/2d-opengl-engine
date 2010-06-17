#include "InputHandler.h"


namespace Prominence {

	InputHandler::InputHandler(Logger &logger) : m_Logger(logger)
	{
		FreeControllers.push_back(new KeyboardA());
		FreeControllers.push_back(new KeyboardB());
		
	}

	InputHandler::~InputHandler(void)
	{
	}

	void InputHandler::FreeHandle(InputDevice &InputDevice)
	{
	}

	void InputHandler::Poll()
	{
		//Loop through free handles
		//If start is pressed, check with player handler to create a plyer
		//if player is created, controller is now used
	}

	InputDevice * InputHandler::NewPlayer()
	{
		std::vector<InputDevice *>::iterator i;
		for (i = FreeControllers.begin(); i != FreeControllers.end(); ++i)
		{
			if ( (*i)->GetStart() )
				return (*i);
		}
		return NULL;
	}

	void InputHandler::UseController(InputDevice * id)
	{
		std::vector<InputDevice *>::iterator i;
		for (i = FreeControllers.begin(); i != FreeControllers.end(); ++i)
		{
			if ( (*i) == id )
			{
				m_Logger.Outputf(P_INFO, INPUT, "Found device, binding it.\n");
				UsedControllers.push_back( (*i) );
				FreeControllers.erase(i);
				return;
			}
		}
		m_Logger.Outputf(P_INFO, INPUT, "Couldn't find device.\n");
	}

}