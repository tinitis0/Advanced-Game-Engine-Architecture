/*! \file application.cpp
*/

#include "engine_pch.h"
#include <glad/glad.h>
#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
#include "Platform/GLFW/GLFWSystem.h"
#endif  

#ifdef NG_PLATFORM_WINDOWS
	#include "Platform/Windows/winTimer.h"
#endif

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Rendering/indexBuffer.h"
#include "Rendering/vertexBuffer.h"
#include "Rendering/vertexArray.h"
#include "Rendering/Shader.h"
#include "Rendering/Textures.h"
#include "Platform/OpenGL/OpenGL_VertexArray.h"
#include "Platform/OpenGL/OpenGL_Shader.h"
#include "Platform/OpenGL/OpenGL_Textures.h"
#include "Rendering/SubTexture.h"
#include "Rendering/FCVertex.h"
#include "Rendering/cubeVertex.h"
#include "Rendering/VertexNormalised.h"
#include "Rendering/UniformBuffer.h"
#include "Platform/OpenGL/OpenGL_RenderCommands.h"
#include "Rendering/TextureManager.h"
#include "Events/Commands.h"
//#include "Platform/EnTT/EnTTLayer.h"
#include "Platform/GLFW/ImGuiHelper.h"


#include "Platform/Renderer/3D_Renderer.h"
#include "Platform/Renderer/2D_Renderer.h"

namespace Engine {

	//BufferLayout cubeVertex::s_layout = { shaderDataType::Float3, shaderDataType::Float3, shaderDataType::Float2 }; //!< Initialising s_layout for cubeVertices
	VertexBufferLayout FCVertex::s_layout = { shaderDataType::Float3, {shaderDataType::Byte4, true} }; //!< Initialising s_layout for FCVertex FLOAT3 & BYTE4
	VertexBufferLayout VertexNormalised::s_layout = { {shaderDataType::Float3, {shaderDataType::Short3, true}, {shaderDataType::Short2, true}}, 24 }; //!< Initialising s_layout for VertexNormalised 24 bytes 1 FLOAT, SHORT2 & SHORT3

	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application(ApplicationProps props)
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		// Start systems

		// Start log
		m_logSystem.reset(new Logger);
		m_logSystem->start();

		// Start windows system
#ifdef NG_PLATFORM_WINDOWS
		m_windowsSystem.reset(new GLFWSystem);
#endif
		m_windowsSystem->start();

		// Start Timer (not system)
#ifdef NG_PLATFORM_WINDOWS
		m_Timer.reset(new winTimer); //!< Timer
#else
		m_Timer.reset(new ChronoTimer);
#endif
		m_Timer->start();

		m_physics.reset(new PhysicsSystem);
		m_physics->start();

		//Make a resource manager
		m_rm.reset(new ResourceManager);

		//Give the physics system the resource manager
		m_physics->listener.rManager = m_rm;

		//WindowProperties props("My Game Engine", 900, 700); //!< Window Properties
		m_window.reset(windows::create(props.winProps)); //!< Creates window using properties

		// Window
		m_window->getEventHandler().setOnCloseCallBack(std::bind(&Application::onClose, this, std::placeholders::_1)); //!< Tells event handler when window is closed call close
		m_window->getEventHandler().setOnResizeCallBack(std::bind(&Application::onResize, this, std::placeholders::_1)); //!< Tells event handler when window is resized call resize
		m_window->getEventHandler().setOnWinMoveCallBack(std::bind(&Application::onWinMove, this, std::placeholders::_1)); //!< Tells event handler when window is moved call move
		m_window->getEventHandler().setOnFocusCallBack(std::bind(&Application::onFocus, this, std::placeholders::_1)); //!< Tells event handler when window is focused call focus
		m_window->getEventHandler().setOnLostFocusCallBack(std::bind(&Application::onLostFocus, this, std::placeholders::_1)); //!< Tells event handler when window has lost focus call lost focus

		// Keyboard
		m_window->getEventHandler().setOnKeyPressedCallBack(std::bind(&Application::onKeyPressed, this, std::placeholders::_1)); //!< Tells event handler when key is pressed call key pressed
		m_window->getEventHandler().setOnKeyReleasedCallBack(std::bind(&layerStack::onKeyReleased, &m_layerStack, std::placeholders::_1)); //!< Tells event handler when key is released call key released

		// Mouse
		m_window->getEventHandler().setOnMousePressedCallBack(std::bind(&layerStack::onMousePressed, &m_layerStack, std::placeholders::_1)); //!< Tells event handler when mouse button is pressed call mouse pressed
		m_window->getEventHandler().setOnMouseReleasedCallBack(std::bind(&layerStack::onMouseReleased, &m_layerStack, std::placeholders::_1)); //!< Tells event handler when mouse button is released call mouse released
		m_window->getEventHandler().setOnMouseMovedCallBack(std::bind(&layerStack::onMouseMoved, &m_layerStack, std::placeholders::_1)); //!< Tells event handler when mouse moves call mouse move
		m_window->getEventHandler().setOnMouseScrollCallBack(std::bind(&layerStack::onMouseWheel, &m_layerStack, std::placeholders::_1)); //!< Tells event handler when mouse scrolls call mouse scroll

		Renderer2D::init(props);

		ImGuiHelper::init();

		InputPoller::setNativeWindow(m_window->getNativeWindow());

		m_Timer->reset(); //!< Reset Timer
	}
	// Window
	bool Application::onClose(windowCloseEvent & e)
	{
		e.handle(true); //!< Handle this
		m_running = false; //!< Application not running
		return e.handled(); //!< Handled
	}

	bool Application::onResize(WindowResizeEvent & e)
	{
		e.handle(true); //!< Handle this
		auto& size = e.getSize(); //!< Size is window size X & Y
		//Logger::info("Window Resize Event: ({0}, {1})", size.x, size.y); //!< Log the size of the window
		return e.handled(); //!< Handled
	}

	bool Application::onWinMove(WindowMoveEvent & e)
	{
		e.handle(true); //!< Handle this
		auto& pos = e.getPos(); //!< Windows position
		//Logger::info("Window Move Event: ({0}, {1})", pos.x, pos.y); //!< Logs the position of the window on X & Y axis
		return e.handled(); //!< Handled
	}

	bool Application::onFocus(WindowFocus & e)
	{
		e.handle(true); //!< Handle this
		m_focus = true; //!< Window is focused
		return e.handled(); //!< Handled
	}

	bool Application::onLostFocus(WindowLostFocus & e)
	{
		e.handle(true); //!< Handle this
		m_focus = false; //!< Window is not focused
		return e.handled(); //!< Handled
	}
	
	// Keyboard
	void Application::onKeyPressed(KeyPressed & e)
	{
		switch (e.getKeyCode())
		{
		case NG_KEY_ESCAPE:
			m_running = false;
			e.handle(true);
			break;
		case NG_KEY_F10:
			m_window->setFullscreenMode(!m_window->isFullScreenActive());
			e.handle(true);
			break;
		default:
			m_layerStack.onKeyPressed(e);
		}
	}

	Application::~Application()
	{
		// Stop systems

		m_physics->stop();

		// Stop windows system
		m_windowsSystem->stop(); //!< Stop windows system on destruction

		// Stop logger
		m_logSystem->stop(); //!< Stop Logger on Destruction


	}

	void Application::run()
	{
		

		Renderer3D::init(); //!< Initialise the 3D renderer


		float timestep = 0.f;

		RendererCommon::actionCommand(RendererCommon::clearCommand); //!< Clear Colour (Background Colour)

		std::chrono::system_clock::time_point a = std::chrono::system_clock::now(); //!< Get the current time point
		std::chrono::system_clock::time_point b = std::chrono::system_clock::now(); //!< Get the current time point again

		float advance; //!< Advance

		while (m_running)
		{
			a = std::chrono::system_clock::now(); //!< Get the current time point every frame
			std::chrono::duration<double, std::milli> worktime = a - b; //!< create "work time" as an array of doubles and milliseconds, using the starting timestep and current timestep
			
			if (worktime.count() < 10.0) //When workcount makes it to 10
			{
				std::chrono::duration<double, std::milli> deltaMs(10.0 - worktime.count()); //!< set delta_ms to be 10 minus the worktime count
				auto deltaMsDuration = std::chrono::duration_cast<std::chrono::milliseconds>(deltaMs); //!< cast the duration to the delta_ms value
				std::this_thread::sleep_for(std::chrono::milliseconds(deltaMsDuration.count())); //!< Limit the framerate by waiting so that the system only updates every time for 60 fps
			}
			
			b = std::chrono::system_clock::now(); //Get the current timestep
			std::chrono::duration<double, std::milli> sleep_time = b - a; //Set the sleep time

			timestep = m_Timer->getElapsedTime(); //!< Time elapsed

			// Reset Timer
			m_Timer->reset();

			//Logger::trace("FPS {0}", 1.0f / timestep);
			if (timestep < 0.2)
			{
				m_physics->m_world->update(timestep);
			}
			else
			{
				m_physics->m_world->update(0.2f);
			}

			m_layerStack.update(timestep);
			m_layerStack.render();
			//Logger::info(timestep);
			m_window->onUpdate(timestep); //!< Update the window
		}
		
	}
}
