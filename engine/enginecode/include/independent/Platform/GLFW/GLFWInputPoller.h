#pragma once
/*! \file GLFWInputPoller.h */
#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine
{
	/*! \class GLFWInputPoller
	* API Agnostic Input Poller spcific to the GLFW system
	*/
	class GLFWInputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!< Key pressed
		static bool isMouseButtonPressed(int32_t mouseButton); //!< Is mouse button pressed
		static glm::vec2 getMousePos(); //!< Current mouse position
		static void setCurrentWindow(GLFWwindow* newWin) { m_window = newWin; } //!< Setter for current window
	private:
		static GLFWwindow* m_window; //!< Current GLFW Window 
	};
}