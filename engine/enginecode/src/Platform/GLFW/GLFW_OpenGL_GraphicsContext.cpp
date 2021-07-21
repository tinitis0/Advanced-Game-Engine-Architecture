/*! \file GLFW_OpenGL_GraphicsContext.cpp */

#include "engine_pch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Platform/GLFW/GLFW_OpenGL_GraphicsContext.h"
#include "Platform/GLFW/ImGuiHelper.h"
#include "systems/Logger.h"

namespace Engine
{

	void errorGLCallBack (GLenum source,
						GLenum type,
						GLuint id,
						GLenum severity,
						GLsizei length,
						const GLchar* message,
						const void* userParam) //!< OpenGL error callback
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH : //!< High Severity Message
			Logger::error(message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM: //!< Medium Severity Message
			Logger::warn(message);
			break;
		case GL_DEBUG_SEVERITY_LOW: //!< Low Severity Message
			Logger::info(message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: //!< Notification
			//Logger::trace(message);
			break;
		}
	}

	GLFW_OpenGl_GraphicsContext::~GLFW_OpenGl_GraphicsContext()
	{
		ImGuiHelper::shutdown();
	}

	void GLFW_OpenGl_GraphicsContext::init()
	{
		glfwMakeContextCurrent(m_window); //!< Setting window to GLFW window
		auto result = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); //!< Loading OpenGL via glad
		if (!result) Logger::error("Could not create OpenGL Context for this current GLFW Window: {0}", result); //!< Error message when OpenGL cannot be created on the GLFW window
	
		// OpenGL Debugging
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(errorGLCallBack, nullptr); //!< Debug Callback
	}
	void GLFW_OpenGl_GraphicsContext::swapBuffers()
	{
		glfwSwapBuffers(m_window); //!< Swaps front and back buffers
	}
	void GLFW_OpenGl_GraphicsContext::updateViewport(int32_t width, int32_t height)
	{
		glViewport(0, 0, width, height);
	}
}