/*! \file GLFWInputPoller.cpp */

#include "engine_pch.h"
#include "Platform/GLFW/GLFWInputPoller.h"

namespace Engine
{
	GLFWwindow* GLFWInputPoller::m_window = nullptr;

	bool GLFWInputPoller::isKeyPressed(int32_t keyCode)
	{
		if (m_window)
		{
			auto answer = glfwGetKey(m_window, keyCode); //!< Gte Key Pressed
			return answer == GLFW_PRESS || answer == GLFW_REPEAT; //!< Return Answer Key is pressed & Repeat rate
		}
		return false; //!< Key Not Pressed
	}

	bool GLFWInputPoller::isMouseButtonPressed(int32_t mouseButton)
	{
		if (m_window)
		{
			auto answer = glfwGetMouseButton(m_window, mouseButton); //!< Get Mouse Button Pressed
			return answer == GLFW_PRESS; //!< Return Answer as Mouse Button Pressed
		}
		return false; //!< Mouse Button Not pressed
	}

	glm::vec2 GLFWInputPoller::getMousePos()
	{
		if (m_window)
		{
			double x, y; //!< Mouse.x & Mouse.y
			glfwGetCursorPos(m_window, &x, &y); //!< Get cursor position
			return glm::vec2(static_cast<float>(x), static_cast<float>(y)); //!< Return position
		}
		return { -1.f, 1.f }; //!< Don't return psoition
	}

}