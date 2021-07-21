/* \file layerStack.h */
#pragma once

#include "core/layer.h"

namespace Engine
{
	class layerStack
	{
	public:
		layerStack() { m_stack.reserve(10); }
		~layerStack(); //!< Destructor

		void push(Layer* layer);
		void pop();

		void update(float timestep);
		void render();

		bool onKeyPressed(KeyPressed& e);
		bool onKeyReleased(KeyReleased& e);
		bool onMousePressed(MousePressed& e);
		bool onMouseReleased(MouseReleased& e);
		bool onMouseWheel(MouseScroll& e);
		bool onMouseMoved(MouseMoved& e);

		void setActive(const char * layerName, bool activeState);
		void setAllActive(bool activeState);
		void setDisplayed(const char * layerName, bool displayState);
		void setAllDisplayed(bool displayState);
		void setFocused(const char * layerName, bool focusedState);
		void setAllFocused(bool focusedState);

		std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_stack.begin(); }
		std::vector<std::shared_ptr<Layer>>::iterator end() { return m_stack.end(); }
		std::vector<std::shared_ptr<Layer>>::reverse_iterator rbegin() { return m_stack.rbegin(); }
		std::vector<std::shared_ptr<Layer>>::reverse_iterator rend() { return m_stack.rend(); }

		std::vector<std::shared_ptr<Layer>>::const_iterator begin() const { return m_stack.begin(); }
		std::vector<std::shared_ptr<Layer>>::const_iterator end() const { return m_stack.end(); }
		std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rbegin() const { return m_stack.rbegin(); }
		std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rend() const { return m_stack.rend(); }
	private:
		std::vector<std::shared_ptr<Layer>> m_stack;
	};
}