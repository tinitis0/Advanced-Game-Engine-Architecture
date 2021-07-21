/* \file widgets.h */

#include "engine_pch.h"
#include "UI/widgets.h"
#include "UI/containers.h"
#include "UI/modalWindow.h"


namespace Engine
{
	void Widget::updatePosition(glm::ivec2& relativePosition)
	{
		m_position = relativePosition;
	}

	void Widget::updateSize()
	{
		m_parent->updateSize();
	}

	Spacer::Spacer(glm::ivec2 size)
	{
		m_size = size;
		m_position = { 0,0 };
	}
	Spacer::Spacer(int32_t sizeX, int32_t sizeY)
	{
		m_size = glm::ivec2(sizeX, sizeY);
		m_position = { 0,0 };
	}

	Label::Label(glm::ivec2 size, const char * labelText) : m_text(labelText)
	{
		m_size = size;
		m_position = {0,0};
	}
	Label::Label(int32_t sizeX, int32_t sizeY, const char * labelText) : m_text(labelText)
	{
		m_size = glm::ivec2(sizeX, sizeY);
		m_position = { 0,0 };
		m_textPosition = { 0,0 };
	}

	void Label::onRender() const
	{
		Renderer2D::submit(m_text, m_textPosition, m_col->foreground);
	}

	void Label::updatePosition(glm::ivec2& relativePosition)
	{
		m_position = relativePosition;
		glm::ivec2 center = m_position + m_size / 2;

	}

	void Button::onRender() const
	{
		Renderer2D::submit(Quad::createTopLeftSize(m_position, m_size), glm::vec4(0.5, 0.5, 0.5, 1.0));

	}

	void Button::onMousePressed(glm::ivec2& mousePosition, int32_t button)
	{
		if (button ==NG_MOUSE_BUTTON_1)
		{
			bool clickedOn =
				m_position.x <= mousePosition.x && mousePosition.x <= m_position.x + m_size.x &&
				m_position.y <= mousePosition.y && mousePosition.y <= m_position.x + m_size.y;
		
			if (clickedOn) m_callback();			
		}
	}




}