#pragma once

/*! \file OpenGL_RenderCommands.h */

#include "Platform/Renderer/renderCommands.h"
#include "Platform/Renderer/RendererCommon.h"

namespace Engine
{
	/*! \class OpenGLSetClearColourCommand */
	class OpenGLSetClearColourCommand : public renderCommands
	{
	private:
		float m_r, m_g, m_b, m_a; //!< RGBA Floats
	public:
		OpenGLSetClearColourCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {}; //!< OpenGL Command that takes the RGBA float values
		void action() override; //!< Override Action
	};

	/*! \class OpenGLGetClearColourAndDepthBufferCommand */
	class OpenGLGetClearColourAndDepthBufferCommand : public renderCommands
	{
	public:
		OpenGLGetClearColourAndDepthBufferCommand() {}; //!< OpenGL Command to clear depth & colour buffers
		void action() override; //!< Override Action
	};

	/*! \class OpenGLSetDepthTest */
	class OpenGLGetSetDepthTest : public renderCommands
	{
	private:
		bool m_enabled;
	public:
		OpenGLGetSetDepthTest(bool enabled) : m_enabled(enabled) {} //!< OpenGL Command to set depth testing takes a boolean value
		void action() override; //!< Override Action
	};

	/*! \class OpenGLGetClearDepthBufferCommand */
	class OpenGLGetClearDepthBufferCommand : public renderCommands
	{
	public:
		OpenGLGetClearDepthBufferCommand() {} //!< OpenGL Command to clear depth buffer alone
		void action() override; //!< Override Action
	};

	/*! \class OpenGLGetClearColourBufferCommand */
	class OpenGLGetClearColourBufferCommand : public renderCommands
	{
	public:
		OpenGLGetClearColourBufferCommand() {} //!< OpenGL Command to clear colour buffer alone
		void action() override; //!< Override Action
	};

	/*! \class OpenGLSetBlendCommand */
	class OpenGLGetSetBlendCommand : public  renderCommands
	{
	private:
		bool m_enabled;
	public:
		OpenGLGetSetBlendCommand(bool enabled) : m_enabled(enabled) {} //!< OpenGL Command to set blend
		void action() override; //!< Override Action
	};

	/*! \class OpenGLSetAlphaBlendFunction */
	class OpenGLGetSetAlphaBlendFunction : public renderCommands
	{
	public:
		OpenGLGetSetAlphaBlendFunction() {} //!< OpenGL Command to set blend function
		void action() override; //!< Override Action
	};

	class OpenGLGetSetWireFrame : public renderCommands
	{
	public:
		OpenGLGetSetWireFrame() {} //!< OpenGL Command to set blend function
		void action() override; //!< Override Action
	};
}
