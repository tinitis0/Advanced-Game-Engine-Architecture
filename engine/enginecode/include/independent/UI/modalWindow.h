/* \file modalWindow.h*/
#pragma once

#include "Platform/Renderer/2D_Renderer.h"
#include "core/application.h"
#include "UI/UIComponent.h"
#include "UI/containers.h"

namespace Engine
{
	class ModalWindow : public UIComponent
	{
	public:
		ModalWindow(); //!< Constructor

		MenuColour m_menuColour;
		void show() { m_active = true; } //!< Show the modal window
		void hide() { m_active = false; } //!< Hide the modal window
		void onRender() const override; //!< On render override
		void addContainer(HorizontalContainer& container); //!< Function to add horizontal containers
		virtual void updateSize() override; //!< Update size override
		virtual void updatePosition(glm::ivec2& relativePosition) override {}; //!< Update the position

		virtual void onMouseMoved(glm::ivec2& mousePosition) override; //!< on mouse moved event override
		virtual void onMousePressed(glm::ivec2& mousePosition, int32_t button) override; //!< on mouse pressed event override
		virtual void onMouseReleased(glm::ivec2& mousePosition, int32_t button) override; //!< on mouse released event override

		bool isShown() { return m_active; } //!< getter for the active status boolean
		static int32_t padding; //!< padding size

	private:
		bool m_active = false; //!< active boolean, for if modal window should be shown
		VertContainer m_container; //!< Vertical container
	};
}
