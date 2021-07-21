/* \file containers.cpp */

#include "engine_pch.h"
#include "UI/containers.h"
#include "UI/modalWindow.h"

namespace Engine
{
#pragma region VertContainer
	VertContainer::VertContainer(ModalWindow * parent)
	{
		//Set the parent
		m_parent = parent;
		//Set the colour
		m_col = parent->m_col; //Parent was a reference in simon's code, but not here apparently. Keep an eye on this, may cause issues
		//Preset the position
		m_position = { 0, 0 };
		//Set the size to be padding * 2
		m_size = { ModalWindow::padding * 2, ModalWindow::padding * 2 };
	}

	void VertContainer::onRender() const
	{
		//For every stored container
		for (auto& container : m_containers)
		{
			//Render them
			container.onRender();
		}
	}

	void VertContainer::addContainer(HorizontalContainer & container)
	{
		//Set this vert container to be the horiz container's parent
		container.setParent(this);
		//Set the horiz container's colour to be the same as the vert container's
		container.m_col = m_col;
		for (auto& widget : container)
		{
			widget->m_col = m_col;
		}

		//Add the horiz container to the container stack
		m_containers.push_back(container);

		//Update the vert container's size
		updateSize();
	}

	void VertContainer::updatePosition(glm::ivec2 & relativePosition)
	{
		//Set the position
		m_position = relativePosition;

		//set the child's positions as the position plus padding
		glm::ivec2 childRelativePosition = m_position + glm::ivec2(ModalWindow::padding, ModalWindow::padding);
		for (auto container : m_containers)
		{
			//Update the container's position
			container.updatePosition(childRelativePosition);
			//Add the container's y size to the relative position, therefore no overlapping containers
			childRelativePosition.y += container.getSize().y;
		}
	}

	void VertContainer::updateSize()
	{
		//Predefine size
		glm::ivec2 size(0);
		//Add padding to the size twice
		size += 2 * glm::ivec2(ModalWindow::padding, ModalWindow::padding);
		//For every container in containers
		for (auto& container : m_containers)
		{
			//Update the size on the x, with padding
			size.x = std::max(size.x, ModalWindow::padding * 2 + container.getSize().x);
			//Update the size on the y
			size.y = container.getSize().y;
		}
		//Set the size
		m_size = size;

		//Update the parent
		m_parent->updateSize();
	}

#pragma endregion

#pragma region HorizContainer
	void HorizontalContainer::updatePosition(glm::ivec2 & relativePosition)
	{
		//set the position
		m_position = relativePosition;
		
		//set the child's positions as the position plus padding
		glm::ivec2 childRelativePosition = m_position + glm::ivec2(ModalWindow::padding, ModalWindow::padding);
		for (auto& widget : m_widgets)
		{
			widget->updatePosition(childRelativePosition);
			childRelativePosition.x += widget->getSize().x;
		}
	}

	void HorizontalContainer::updateSize()
	{
		//Predefine size
		glm::ivec2 size(0);
		//Add the padding to size twice
		size += 2 * glm::ivec2(ModalWindow::padding, ModalWindow::padding);

		for (auto& widget : m_widgets)
		{
			size.x += widget->getSize().x;
			size.y = std::max(size.y, ModalWindow::padding * 2 + widget->getSize().y);
		}
	}

	void HorizontalContainer::onRender() const
	{
		for (auto widget : m_widgets) widget->onRender();
	}

#pragma endregion

}