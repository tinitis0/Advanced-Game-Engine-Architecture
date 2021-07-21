/*! \file GLFWWindowImplem.cpp */

#include "engine_pch.h"
#include "Platform/GLFW/GLFWWindowImplem.h"
#include "Platform/GLFW/GLFW_OpenGL_GraphicsContext.h"
#include "systems/Logger.h"

namespace Engine
{
#ifdef NG_PLATFORM_WINDOWS
	windows* windows::create(const WindowProperties& properties) //!< If compile under windows
	{
		return new GLFWWindowImplem(properties); //!< Create a GLFW window
	}
#endif 

	// Window Implementation
	GLFWWindowImplem::GLFWWindowImplem(const WindowProperties & properties)
	{
		init(properties); //!< Initialises window properties
	}

	// Window Initialisation 
	void GLFWWindowImplem::init(const WindowProperties & properties)
	{
		m_prop = properties;

		m_aspectRatio = static_cast<float> (m_prop.width) / static_cast<float>(m_prop.height); //!< Width divided by height

		if (m_prop.isFullScreen)
		{
			m_nativeWindow = glfwCreateWindow(800, 600, "Window", glfwGetPrimaryMonitor(), NULL); //!< Set fullscreen on primary monitor
		}
		else
		{
			m_nativeWindow = glfwCreateWindow(m_prop.width, m_prop.height, m_prop.title, nullptr, nullptr); //!< Else use windowed at width and height set
		}

		m_gContext.reset(new GLFW_OpenGl_GraphicsContext(m_nativeWindow));
		m_gContext->init();

		glfwSetWindowUserPointer(m_nativeWindow, static_cast<void*>(&m_handler));

		// Windows Events
		glfwSetWindowCloseCallback(m_nativeWindow,
			[](GLFWwindow * window)
		{
			eventHandler* handler = static_cast<eventHandler*>(glfwGetWindowUserPointer(window)); //!< Getting events back
			auto& onWinClose = handler->getOnCloseCallBack(); //!< Close window callback

			windowCloseEvent event; //!< Setting close event as "event"
			onWinClose(event); //!< onWinClose calls the event set (Close)
		}
		);

		glfwSetWindowSizeCallback(m_nativeWindow,
			[](GLFWwindow * window, int newWidth, int newHeight) 
		{
			eventHandler* handler = static_cast<eventHandler*>(glfwGetWindowUserPointer(window));
			auto& onResize = handler->getOnResizeCallBack(); //!< Resize window callback

			WindowResizeEvent event(newWidth, newHeight); //!< Setting Resize event as "event"
			onResize(event); //!< onResize calls the event set (Resize)
		}
		);

		glfwSetWindowPosCallback(m_nativeWindow,
			[](GLFWwindow * window, int newX, int newY)
		{
			eventHandler* handler = static_cast<eventHandler*>(glfwGetWindowUserPointer(window));
			auto& onMove = handler->getOnWinMoveCallBack(); //!< Window move callback

			WindowMoveEvent event(newX, newY); //!< Setting move event as "event"
			onMove(event); //!< onMove calls the event set (Move)
		}
		);

		glfwSetWindowFocusCallback(m_nativeWindow,
			[](GLFWwindow * window, int focus)
		{
			eventHandler* handler = static_cast<eventHandler*>(glfwGetWindowUserPointer(window));
			
			if (focus)
			{
				auto& onFocus = handler->getOnFocusCallBack(); //!< Window focus callback

				WindowFocus event; //!< Setting window focus event as "event"
				onFocus(event); //!< onFocus calls the event set (Focus)
			}
			else
			{
				auto& onLostFocus = handler->getOnLostFocusCallBack(); //!< Window LostFocus callback

				WindowLostFocus event; //!< Setting Lost Focus event as "event"
				onLostFocus(event); //!< onLostFocus calls the event set (LostFocus)
			}
		}
		);

		// Keyboard Events
		glfwSetKeyCallback(m_nativeWindow,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			eventHandler* handler = static_cast<eventHandler*>(glfwGetWindowUserPointer(window));

			if (action == GLFW_PRESS)
			{
				auto& onKeyPressed = handler->getOnKeyPressedCallBack(); //!< Get key pressed callback

				KeyPressed event(key, 0); //!< Key pressed & repeat count set to 0
				onKeyPressed(event); //!< On key press calls event(KeyPressed)
			}
			else if (action == GLFW_REPEAT) //!< If key pressed is repeated
			{
				auto& onKeyPressed = handler->getOnKeyPressedCallBack(); //!< Get key pressed callback

				KeyPressed event(key, 1); //!< Key pressed & repeat count set to 1
				onKeyPressed(event); //!< On key press calls event(KeyPressed)
			}
			else if (action == GLFW_RELEASE) //!< Key is released
			{
				auto& onKeyReleased = handler->getOnKeyReleasedCallBack(); //!< Get key release callback

				KeyReleased event(key); //!< Key released
				onKeyReleased(event); //!< On key release calls event(KeyReleased)
			}
		}
		);

		// Mouse
		glfwSetMouseButtonCallback(m_nativeWindow,
			[](GLFWwindow * window, int button, int action, int mods)
		{
			eventHandler* handler = static_cast<eventHandler*>(glfwGetWindowUserPointer(window));

			if (action == GLFW_PRESS)
			{
				auto& onMousePressed = handler->getOnMousePressedCallBack(); //!< Get mouse button pressed callback

				MousePressed event(button); //!< Button Pressed
				onMousePressed(event); //!< On Mouse Pressed calls event(MousePressed)
			}
			else if (action == GLFW_RELEASE)
			{
				auto& onMouseReleased = handler->getOnMouseReleasedCallBack(); //!< Get mouse button release callback

				MouseReleased event(button); //!< Button released
				onMouseReleased(event); //!< On key release calls event(MouseReleased)
			}
		}
		);

		glfwSetCursorPosCallback(m_nativeWindow,
			[](GLFWwindow* window, double posX, double posY) 
		{
			eventHandler* handler = static_cast<eventHandler*>(glfwGetWindowUserPointer(window));
			auto& onCursorMove = handler->getOnMouseMovedCallBack(); //!< Mouse move callback

			MouseMoved event(posX, posY); //!< Setting mouse moved as "event" (Position X & Position Y)
			onCursorMove(event); //!< onCursorMove calls the event set (Move)
		}
		);

		glfwSetScrollCallback(m_nativeWindow,
			[](GLFWwindow* window, double xOffSet, double yOffSet)
		{
			eventHandler* handler = static_cast<eventHandler*>(glfwGetWindowUserPointer(window));
			auto& onScroll = handler->getOnMouseScrollCallBack(); //!< Mouse scroll callback

			MouseScroll event(xOffSet, yOffSet); //!< Setting MouseScroll as "event" (xOffSet & yOffSet)
			onScroll(event); //!< onScroll calls the event set (Scroll)
		}
		);

		glfwGetWindowPos(m_nativeWindow, &m_nonFullscreenPos.x, &m_nonFullscreenPos.y);
		glfwGetWindowSize(m_nativeWindow, &m_nonFullscreenSize.x, &m_nonFullscreenSize.y);

		setFullscreenMode(m_prop.isFullScreen);
	}
	
	// Window Close
	void GLFWWindowImplem::close()
	{
		glfwDestroyWindow(m_nativeWindow); //!< Destroys the window
	}

	// Window Update
	void GLFWWindowImplem::onUpdate(float timestep)
	{
		glfwPollEvents(); //!< Searches for events and then processes them
		m_gContext->swapBuffers();
	}

	void GLFWWindowImplem::onResize(WindowResizeEvent & e)
	{
		m_prop.width = e.getSize().x;
		m_prop.height = e.getSize().y;

		m_gContext->updateViewport(m_prop.width, m_prop.height);
	}

	// Window VSync
	void GLFWWindowImplem::setVSync(bool VSync)
	{
		m_prop.isVSync = VSync; 
		if (VSync)
		{
			glfwSwapInterval(1); //!< Synchronized to monitor settings
		}
		else
		{
			glfwSwapInterval(0); //!< Run as fast it can
		}
	}
	void GLFWWindowImplem::setFullscreenMode(bool fullscreenState)
	{
		if (isFullScreenActive() == fullscreenState) return;

		if (fullscreenState)
		{

			glfwGetWindowPos(m_nativeWindow, &m_nonFullscreenPos.x, &m_nonFullscreenPos.y);
			glfwGetWindowSize(m_nativeWindow, &m_nonFullscreenSize.x, &m_nonFullscreenSize.y);

			const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

			glfwSetWindowMonitor(m_nativeWindow, m_monitor, 0, 0, mode->width, mode->height, 0);

			m_gContext->updateViewport(mode->width, mode->height);

			m_prop.width = mode->width;
			m_prop.height = mode->height;
		}
		else
		{
			glfwSetWindowMonitor(m_nativeWindow, nullptr, m_nonFullscreenPos.x, m_nonFullscreenPos.y, m_nonFullscreenSize.x, m_nonFullscreenSize.y, 0);
			
			m_gContext->updateViewport(m_nonFullscreenSize.x, m_nonFullscreenSize.y);

			m_prop.width = m_nonFullscreenSize.x;
			m_prop.height = m_nonFullscreenSize.y;
		}

		m_prop.isFullScreen = !m_prop.isFullScreen;
		eventHandler* handler = static_cast<eventHandler*>(glfwGetWindowUserPointer(m_nativeWindow));
		auto& onResize = handler->getOnResizeCallBack();

		WindowResizeEvent e(m_prop.width, m_prop.height);

		onResize(e);

	}
	void GLFWWindowImplem::setSize(const glm::ivec2 & size)
	{
		if (m_nativeWindow)
		{
			glfwSetWindowSize(m_nativeWindow, size.x, size.y);
		}
	}
}