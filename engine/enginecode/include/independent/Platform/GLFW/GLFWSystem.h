/*! \file GLFWSystem.h */
#pragma once

#include "systems/system.h"

#include <GLFW/glfw3.h>
#include "systems/Logger.h"

namespace Engine
{
	/*! \class GLFWSystem */
	class GLFWSystem : public System
	{
		virtual inline void start(SystemSignal init = SystemSignal::None, ...) override //!< Start system
		{
			auto errorCode = glfwInit(); //!< Error Code
			if (!errorCode)
			{
				Logger::error("Cannot initialise GLFW {0}", errorCode); //!< Error message for the init of GLFW
			}
		}
		virtual inline void stop(SystemSignal close = SystemSignal::None, ...) override //!< Stop system
		{
			glfwTerminate(); //!< GLFW Terminate
		}
	};
}