#pragma once

#include "Export.h"

#include <iostream>
#include <fstream>
#include <string>

namespace Prominence {

	enum Tolerance {FULL_TOLERANCE, WARNING_TOLERANCE, ERROR_TOLERANCE, NO_TOLERANCE};
	enum Priority {P_INFO, P_WARNING, P_ERROR};
	enum L_Mode {OFF_MODE, CONSOLE_MODE, FILE_MODE};
	enum Topic {WINDOW, VIDEO, AUDIO, INPUT, TIMER, GAME, ENGINE, OTHER };
	const std::string priorities[] = { "INFO", "WARNING", "ERROR" };
	const std::string topics[] = { "WINDOW", "VIDEO", "AUDIO", "INPUT", "TIMER", "GAME", "ENGINE", "OTHER" };


	class DECLSPEC Logger
	{
	private:
		Tolerance m_Tolerance;
		L_Mode m_Mode;
		std::string m_File;
		std::ofstream * m_FStream;
	public:
		Logger(void);
		~Logger(void);
		void Outputf (Priority priority, Topic topic, const char *format, ...) const;
		void SetTolerance (Tolerance tolerance) { m_Tolerance = tolerance; }
	};

} //Exit Prominence Namespace