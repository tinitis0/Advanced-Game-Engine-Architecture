/*! \file application.h */
#pragma once

#include "systems/Logger.h"
#include "timer.h"
#include "Events/events.h"
#include "Platform/Windows/window.h"
#include "core/inputPoller.h"
#include "core/layerStack.h"
#include "systems/physicsSystem.h"
#include "systems/AudioManager.h"
#include "core/resources.h"

//TEMP
#include "entt/entt.hpp"

namespace Engine {

	struct ApplicationProps
	{
		WindowProperties winProps;
		uint32_t vertexCapacity3D = 4000;
		uint32_t indecCapacity3D = 1000;
		uint32_t batchSize3D = 4000;
		uint32_t batchSize2D = 8192;
		const char * fontFilePath = "./assets/Fonts/BadaBoom BB.TTF";
		uint32_t characterSize = 86;
	};

	/*!
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(ApplicationProps props); //!< Constructor

		std::shared_ptr<Logger> m_logSystem; //!< Log System
		std::shared_ptr<System> m_windowsSystem; //!< Window System

		std::shared_ptr<windows> m_window; //!< Window
		std::shared_ptr<Timer> m_Timer; //!< Timer 
		std::shared_ptr<PhysicsSystem> m_physics; //!< pointer to the physics system
		std::shared_ptr<AudioManager> m_audio;
		std::shared_ptr<ResourceManager> m_rm; //!< pointer to the resource manager
		

		// Window
		bool onClose(windowCloseEvent & e); //!< Runs when window closes
		bool onResize(WindowResizeEvent & e); //!< Run when the window is resized by user
		bool onWinMove(WindowMoveEvent & e); //!< Run when window is moved
		bool onFocus(WindowFocus & e); //!< Run when window is focused
		bool onLostFocus(WindowLostFocus & e); //!< Run when window has lost focus
		// Keyboard
		void onKeyPressed(KeyPressed & e); //!< Run when key is pressed
		bool onKeyRelease(KeyReleased & e); //!< Run when key is released
		// Mouse
		bool onMousePressed(MousePressed & e); //!< Run when mouse button is pressed
		bool onMouseReleased(MouseReleased & e); //!< Run when mouse button is released
		bool onMouseMove(MouseMoved & e); //!< Run when mouse moves
		bool onMouseScroll(MouseScroll & e); //!< Run when mouse scroll

	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?
		bool m_focus = true; //!< Is the application focused?
		

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		std::shared_ptr<windows> getWindow() { return m_window; } //!< getter for the window
		std::shared_ptr<ResourceManager> getRM() { return m_rm; } //!< getter for the resource manager



		rp3d::PhysicsWorld* getWorld() { return m_physics->m_world; } //!< Getter for the physics world
		rp3d::PhysicsCommon& getPhysicsCommon() { return m_physics->m_3DPhysCommon; } //!< getter for the physics common
		std::shared_ptr<AudioManager> getAudioManager() { return m_audio; } //!< getter for the audio manager
		//std::shared_ptr<Textures> getTexture() { return m_texture; }

		layerStack m_layerStack;
		void run(); //!< Main loop
		entt::registry m_registry; //!< registry, contains entities (Namely m_entities) as well as the components
		std::vector<entt::entity> m_entities; //!< stack of entities
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}