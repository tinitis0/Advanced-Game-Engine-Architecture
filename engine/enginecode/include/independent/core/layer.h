/* \file layer.h */
#pragma once

#include <string>
#include "independent/Platform/Windows/window.h"

namespace Engine
{
	class Layer
	{
	public:
		Layer(const char * name) : m_name(name) {};

		virtual void onAttach() {} //!< Runs when layer is attached
		virtual void onDetach() {} //!< Runs when layer is detached
		virtual void onRender() {} //!< Runs when layer is rendered
		virtual void onUpdate(float timestep) {} //!< Runs every frame
		virtual void onResize(WindowResizeEvent& e) {} //!< Runs when layers window is resized

		inline const char * getName() const { return m_name; } //!< Accesor
		inline void setDisplayed(bool displayStatus) { m_isDisplayed = displayStatus; }
		inline void setActive(bool activeStatus) { m_isActive = activeStatus; }
		inline void setFocused(bool focusedStatus) { m_isFocused = focusedStatus; }
		inline const bool isDisplayed() const { return m_isDisplayed; }
		inline const bool isActive() const { return m_isActive; }
		inline const bool isFocused() const { return m_isFocused; }

		virtual void onKeyPressed(KeyPressed & e) { e.handle(false); }
		virtual void onKeyReleased(KeyReleased & e) { e.handle(false); }
		virtual void onMousePressed(MousePressed & e) { e.handle(false); }
		virtual void onMouseReleased(MouseReleased & e) { e.handle(false); }
		virtual void onMouseWheel(MouseScroll & e) { e.handle(false); }
		virtual void onMouseMove(MouseMoved & e) { e.handle(false); }

	protected:
		const char * m_name; //!< Name, useful for debugging
		bool m_isDisplayed = true; //!< Should this layer be rendered
		bool m_isActive = true; //!< Should the layer be updated
		bool m_isFocused = true; //!< Should this layer be getting events
	};
}
