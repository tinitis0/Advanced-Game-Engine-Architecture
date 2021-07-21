/*! \file GLFW_OpenGL_GraphicsContext.h */
#pragma once

#include "Platform/Windows/graphicsContext.h"

namespace Engine
{
	/*! \class GLFW_OpenGL_GraphicsContext.h */
	class GLFW_OpenGl_GraphicsContext : public GraphicsContext
	{
	public:
		GLFW_OpenGl_GraphicsContext(GLFWwindow* window) : m_window(window) {} //!< Constructor
		virtual ~GLFW_OpenGl_GraphicsContext() override;
		virtual void init() override; //!< Initialise grahics context for given windowing API
		virtual void swapBuffers() override; //!< Swap front and back buffers (double buffering)
		virtual void updateViewport(int32_t width, int32_t height) override;
	
	private:
		GLFWwindow* m_window; //!< Pointer to GLFW window
	};
}