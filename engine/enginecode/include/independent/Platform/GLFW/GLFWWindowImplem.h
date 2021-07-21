/*! \file GLFWWindowImplem.h */
#pragma once

#include <GLFW/glfw3.h>
#include "Platform/Windows/window.h"

namespace Engine
{
	/*! \class GLFWWindowImplem */

	class GLFWWindowImplem : public windows
	{
	public:
		GLFWWindowImplem(const WindowProperties& properties); //!< Constructor
		virtual void init(const WindowProperties& properties) override; //!< Initialise window with properties
		virtual void close() override; //!< Close window
		virtual void onUpdate(float timestep) override; //!< Update the window
		virtual void onResize(WindowResizeEvent & e) override;
		virtual void setVSync(bool VSync) override; //!< Setting VSync On / Off
		virtual inline unsigned int getWidth() const override { return m_prop.width; }; //!< Get width of window
		virtual inline unsigned int getHeight() const override { return m_prop.height; }; //!< Get height of window
		virtual inline void* getNativeWindow() const override { return m_nativeWindow; };
		virtual inline bool isFullScreenActive() const override { return m_prop.isFullScreen; }; //!< Is the screen fullscreen?
		virtual inline bool isVSyncActive() const override { return m_prop.isVSync; }; //!< Is VSync On?
		virtual void setFullscreenMode(bool fullscreenState) override;
		virtual void setSize(const glm::ivec2& size);

	private:
		WindowProperties m_prop; //!< Properties
		GLFWwindow * m_nativeWindow; //!< Native GLFW window
		float m_aspectRatio; //!< Aspect ratio of window
		GLFWmonitor * m_monitor; // Native monitor in which the window is rendered
		glm::ivec2 m_nonFullscreenPos; // Last known pos when not in fullscreen
		glm::ivec2 m_nonFullscreenSize; // Last know window size when not in fullscreen
	};
}