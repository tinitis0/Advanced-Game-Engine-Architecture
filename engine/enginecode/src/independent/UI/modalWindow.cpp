/* \file modalWindow.cpp*/

#include "engine_pch.h"
#include "UI/modalWindow.h"
#include "UI/containers.h"


namespace Engine
{
	int32_t ModalWindow::padding = 5;

	ModalWindow::ModalWindow()
	{
		glm::ivec2 winSize = Application::getInstance().getWindow()->getSize();
		m_position = (winSize / 2);
		m_size = (glm::ivec2(0.f));
		m_menuColour = (MenuColour());
		m_col = &m_menuColour;
		m_container = VertContainer(this);
		m_container.updatePosition(m_position + glm::ivec2(ModalWindow::padding, ModalWindow::padding));
	}

	void ModalWindow::onRender() const
	{
		if (m_active)
		{
			glm::ivec2 windowSize = Application::getInstance().getWindow()->getSize();
			glm::vec4 bgCover = m_menuColour.background;
			bgCover.a = 0.5f;
			Renderer2D::submit(Quad::createTopLeftSize({ 0.f,0.f }, windowSize), bgCover);
			Renderer2D::submit(Quad::createTopLeftSize(m_position, m_size), m_menuColour.background);
		
			m_container.onRender();
		}
	}
	
	void ModalWindow::addContainer(HorizontalContainer & container)
	{
		m_container.addContainer(container);
	}
	
	void ModalWindow::updateSize()
	{
		glm::ivec2 childSize = m_container.getSize();
		m_size.x = std::max(childSize.x + (padding * 2), m_size.x);
		m_size.y = std::max(childSize.y + (padding * 2), m_size.y);
	
		glm::ivec2 windowSize = Application::getInstance().getWindow()->getSize();
		
	
		m_position = (windowSize - m_size) / 2;
		m_container.updatePosition(m_position + glm::ivec2(ModalWindow::padding, ModalWindow::padding));
	}

	void ModalWindow::onMousePressed(glm::ivec2& mousePosition, int32_t button)
	{
		for (auto& hzContainer : m_container)
		{
			for (auto& Widget : hzContainer)
			{
				Widget->onMousePressed(mousePosition, button);
			}
		}

	}
	void ModalWindow::onMouseReleased(glm::ivec2& mousePosition, int32_t button)
	{
		for (auto& hzContainer : m_container)
		{
			for (auto& Widget : hzContainer)
			{
				Widget->onMouseReleased(mousePosition, button);
			}
		}
	}
	void ModalWindow::onMouseMoved(glm::ivec2& mousePosition)
	{
		for (auto& hzContainer : m_container)
		{
			for (auto& Widget : hzContainer)
			{
				Widget->onMouseMoved(mousePosition);
			}
		}
	}

}