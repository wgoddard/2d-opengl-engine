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
		return NULL;
	}

}