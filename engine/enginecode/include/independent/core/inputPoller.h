/*! \file inputPoller.h */
#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	/*! \ class Input Poller
	* API Agnostic Input Poller
	*/
	class InputPoller
	{
	public:
		static bool isKeyPressed(int32_t); //!< Key pressed
		static bool isMouseButtonPressed(int32_t mouseButton); //!< Is mouse button pressed
		static glm::vec2 getMousePos(); //!< Current mouse position
		static void setNativeWindow(void* nativeWin); //!< Setting window
		inline static float getMouseX() { return getMousePos().x; } //!< Mouse X Position
		inline static float getMouseY() { return getMousePos().y; } //!< Mouse Y Position
	};
}