/* \file UIComponent.h */
#pragma once
#include <glm/glm.hpp>
namespace Engine
{
	struct MenuColour
	{
		glm::vec4 background = {0.0f, 0.25f, 0.0f, 1.0f};
		glm::vec4 foreground = {0.6f, 0.6f, 0.6f, 1.0f};
		glm::vec4  highlight = { 0.75f, 0.75f, 0.75f, 1.0f };
	};

	class UIComponent
	{
	public:
		glm::ivec2 getPos() { return m_position; }
		glm::ivec2 getSize() { return m_size; }
		virtual void updateSize() = 0;
		virtual void updatePosition(glm::ivec2& relativePos) = 0;
		virtual void onRender() const {};
		virtual void onMouseMoved(glm::ivec2& mousePosition) {};
		virtual void onMousePressed(glm::ivec2& mousePosition, int32_t button) {};
		virtual void onMouseReleased(glm::ivec2& mousePosition, int32_t button) {};
		void setParent(UIComponent * parent) { m_parent = parent; }
		UIComponent * getParent() const { return m_parent; }
		MenuColour* m_col = nullptr;

	protected:
		glm::ivec2 m_position; 
		glm::ivec2 m_size;
		UIComponent * m_parent = nullptr;
	};
}