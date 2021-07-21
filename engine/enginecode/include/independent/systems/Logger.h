/*! \file Logger.h */
#pragma once

#include "system.h"
#include <spdlog/spdlog.h>

namespace Engine
{
	/*! \class Logger
	* Logger which will allow the system to log errors & messages
	*/
	class Logger : public System
	{
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...); //!< Start the logger
		virtual void stop(SystemSignal close = SystemSignal::None, ...); //!< Stop the logger

		template<class ...Args>
		static void debug(Args&&... args); //!< Debug

		template<class ...Args>
		static void error(Args&&... args); //!< Error

		template<class ...Args>
		static void info(Args&&... args); //!< Info

		template<class ...Args>
		static void trace(Args&&... args); //!< Trace

		template<class ...Args>
		static void warn(Args&&... args); //!< Warn

		template<class ...Args>
		static void release(Args&&... args); //!< Release

		template<class ...Args>
		static void file(Args&&... args); //!< File 
	private:
		static std::shared_ptr<spdlog::logger> s_consoleLogger; //!< Console logger
		static std::shared_ptr<spdlog::logger> s_fileLogger; //!< File Logger

	};

	template<class ...Args>
	static void Logger::debug(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->debug(std::forward<Args>(args) ...);
#endif
	}

	template<class ...Args>
	static void Logger::error(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->error(std::forward<Args>(args) ...);
#endif
	}

	template<class ...Args>
	static void Logger::trace(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->trace(std::forward<Args>(args) ...);
#endif
	}

	template<class ...Args>
	static void Logger::info(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->info(std::forward<Args>(args) ...);
#endif
	}

	template<class ...Args>
	static void Logger::warn(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->warn(std::forward<Args>(args) ...);
#endif
	}

	template<class ...Args>
	static void Logger::release(Args&&... args)
	{
		s_consoleLogger->trace(std::forward<Args>(args) ...);
	}

	template<class ...Args>
	static void Logger::file(Args&&... args)
	{
		if(s_fileLogger) s_fileLogger->trace(std::forward<Args>(args) ...);
	}
}