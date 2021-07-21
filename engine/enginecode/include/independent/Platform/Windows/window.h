/* \file window.h */
#pragma once
#include "Events/eventHandler.h"
#include "graphicsContext.h"


namespace Engine
{
	// How the window will look
	struct WindowProperties
	{
		char * title; //!< Title of window
		uint32_t width; //!< Width of window
		uint32_t height; //!< Height of window
		bool isFullScreen; //!< Is the window fullscreen?
		bool isVSync; //!< Is VSync set?

		WindowProperties(char * title = "Window", uint32_t width = 800, uint32_t height = 600, bool fullscreen = false) : title(title), width(width), height(height), isFullScreen(fullscreen){} //!< Setting window values
	};

	/* \class window 
	* Abstract windows base class
	*/
	class windows
	{
	public:
		virtual void init(const WindowProperties& properties) = 0; //!< Initialise window with properties
		virtual void close() = 0; //!< Close window
		virtual ~windows() {};
		virtual void onUpdate(float timestep) = 0; //!< Update the window
		virtual void onResize(WindowResizeEvent & e) = 0;
		virtual void setVSync(bool VSync) = 0; //!< Setting VSync On / Off
		virtual unsigned int getWidth() const = 0; //!< Get width of window
		virtual unsigned int getHeight() const = 0; //!< Get height of window
		virtual void* getNativeWindow() const = 0;
		virtual bool isFullScreenActive() const = 0; //!< Is the screen fullscreen?
		virtual bool isVSyncActive() const = 0; //!< Is VSync On?
		virtual void setFullscreenMode(bool fullscreenState) = 0;
		virtual void setSize(const glm::ivec2& size) = 0;		
		inline eventHandler& getEventHandler() { return m_handler; }; //!< Gte the event handler
		static windows* create(const WindowProperties& properties = WindowProperties()); //!< Create window
		glm::vec2 getSize() { return glm::vec2{ getWidth(), getHeight() }; }
	protected:
		eventHandler m_handler; //!< Event handler
		std::shared_ptr<GraphicsContext> m_gContext;
	};
}