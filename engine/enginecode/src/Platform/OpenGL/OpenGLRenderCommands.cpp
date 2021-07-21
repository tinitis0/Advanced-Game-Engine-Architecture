/*! \file RenderCommands.cpp 
* All the render commands functions
*/

#include "engine_pch.h"
#include "Platform/Renderer/renderCommands.h"
#include "Platform/OpenGL/OpenGL_RenderCommands.h"
#include "Rendering/RenderAPI.h"
#include "systems/Logger.h"
#include <glad/glad.h>

namespace Engine
{
	void OpenGLSetClearColourCommand::action()
	{
		glClearColor(m_r, m_g, m_b, m_a); //!< Clear colour with RGBA value set
	}

	void OpenGLGetClearDepthBufferCommand::action()
	{
		glClear(GL_DEPTH_BUFFER_BIT); //!< Clear Depth Buffer
	}

	void OpenGLGetClearColourBufferCommand::action()
	{
		glClear(GL_COLOR_BUFFER_BIT); //!< Clear Colour Buffer
	}

	void OpenGLGetClearColourAndDepthBufferCommand::action()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //!< Clear Colour & Depth Buffers
	}

	void OpenGLGetSetAlphaBlendFunction::action()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //!< Blend Function On Alpha
	}

	void OpenGLGetSetWireFrame::action()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINES); //!< Blend Function On Alpha
		Logger::error("Wireframe");
	}
	void OpenGLGetSetDepthTest::action()
	{
		if (m_enabled) //!< If enabled
		{
			glEnable(GL_DEPTH_TEST);
		}//!< Enable Depth Test
		else
		{
			glDisable(GL_DEPTH_TEST);
		}//!< Disable Depth Test
	}

	void OpenGLGetSetBlendCommand::action()
	{
		if (m_enabled) //!< If enabled
		{
			glEnable(GL_BLEND);
		} //!< Enable blend 
		else
		{
			glDisable(GL_BLEND);
		} //!< Disable blend
	}
}