#include "Logger.h"

namespace Prominence {

	Logger::Logger(void)
	{
		m_Tolerance = WARNING_TOLERANCE;
		m_Mode = CONSOLE_MODE;
		m_File = "logger.txt";
		m_FStream = NULL;
	}

	Logger::~Logger(void)
	{
	}

	void Logger::Outputf(Priority priority, Topic topic, const char *format, ...) const
	{
		if (priority < m_Tolerance || m_Mode == OFF_MODE)
			return;

		char	*pArg=(char *) &format+sizeof(format);

		char buffer[1024];
		_vsnprintf_s(buffer, sizeof(buffer)-1, sizeof(buffer)-1, format, pArg);
		buffer[sizeof(buffer)-1]=0;

		std::cout << '[' <<priorities[priority] << "] " << topics[topic] << ": " << buffer;

	}

} //Exit Prominence namespace