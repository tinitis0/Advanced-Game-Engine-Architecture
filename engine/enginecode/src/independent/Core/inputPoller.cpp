/* \file inputPoller.cpp */
#include "engine_pch.h"
#include "core/inputPoller.h"

#ifdef NG_PLATFORM_WINDOWS
#include "Platform/GLFW/GLFWInputPoller.h"
#endif
namespace Engine
{
#ifdef NG_PLATFORM_WINDOWS
	bool InputPoller::isKeyPressed(int32_t keyCode)
	{
		return GLFWInputPoller::isKeyPressed(keyCode);
	}

	bool InputPoller::isMouseButtonPressed(int32_t mouseButton)
	{
		return GLFWInputPoller::isMouseButtonPressed(mouseButton);
	}

	glm::vec2 InputPoller::getMousePos()
	{
		return GLFWInputPoller::getMousePos();
	}

	void InputPoller::setNativeWindow(void * nativeWin)
	{
		GLFWInputPoller::setCurrentWindow(reinterpret_cast<GLFWwindow*>(nativeWin));
	}
#endif
}