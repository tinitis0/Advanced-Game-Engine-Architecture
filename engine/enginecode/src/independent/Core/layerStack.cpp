/* \file layerStack.cpp */

#include "engine_pch.h"
#include "core/layerStack.h"

namespace Engine
{
	layerStack::~layerStack()
	{
		for (uint32_t i = m_stack.size(); i > 0; i--) pop();
	}

	void layerStack::push(Layer * layer)
	{
		layer->onAttach();
		std::shared_ptr<Layer> tmp(layer);
		m_stack.push_back(tmp);
	}

	void layerStack::pop()
	{
		m_stack.back()->onDetach();
		m_stack.pop_back();
	}

	void layerStack::update(float timestep)
	{
		for (auto& layer : m_stack) if (layer->isActive()) layer->onUpdate(timestep);
	}
	void layerStack::render()
	{
		for (auto& layer : m_stack) if (layer->isDisplayed()) layer->onRender();
	}

	bool layerStack::onKeyPressed(KeyPressed & e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.handled()) layer->onKeyPressed(e);
		return true;
	}

	bool layerStack::onKeyReleased(KeyReleased & e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.handled()) layer->onKeyReleased(e);
		return true;
	}

	bool layerStack::onMousePressed(MousePressed & e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.handled()) layer->onMousePressed(e);
		return true;
	}

	bool layerStack::onMouseReleased(MouseReleased & e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.handled()) layer->onMouseReleased(e);
		return true;
	}

	bool layerStack::onMouseWheel(MouseScroll & e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.handled()) layer->onMouseWheel(e);
		return true;
	}

	bool layerStack::onMouseMoved(MouseMoved & e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.handled()) layer->onMouseMove(e);
		return true;
	}

	void layerStack::setActive(const char * layerName, bool activeState)
	{
		for (auto& layer : m_stack)
		{
			if (layer->getName() == layerName) layer->setActive(activeState);
		}
	}

	void layerStack::setAllActive(bool activeState)
	{
		for (auto& layer : m_stack)
		{
			layer->setActive(activeState);
		}
	}
	void layerStack::setDisplayed(const char * layerName, bool displayState)
	{
		for (auto& layer : m_stack)
		{
			if (layer->getName() == layerName) layer->setDisplayed(displayState);
		}
	}
	void layerStack::setAllDisplayed(bool displayState)
	{
		for (auto& layer : m_stack)
		{
			layer->setDisplayed(displayState);
		}
	}
	void layerStack::setFocused(const char * layerName, bool focusedState)
	{
		for (auto& layer : m_stack)
		{
			if (layer->getName() == layerName) layer->setFocused(focusedState);
		}
	}
	void layerStack::setAllFocused(bool focusedState)
	{
		for (auto& layer : m_stack)
		{
			layer->setFocused(focusedState);
		}
	}
}