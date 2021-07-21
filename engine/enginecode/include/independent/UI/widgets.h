/* \file widgets.h */
#pragma once

#include <glm/glm.hpp>
#include "Platform/Renderer/2D_Renderer.h"
#include "UI/UIComponent.h"


namespace Engine
{
	class HorizontalContainer;
	   
	class Widget : public UIComponent
	{
	public:
		// Update the widget position
		virtual void updatePosition(glm::ivec2& relativePosition) override;
		// Update the widget size
		virtual void updateSize() override;
	};

	class Spacer : public Widget
	{
	public:
		//Give the size for the empty space
		Spacer(glm::ivec2 size);
		//set the size on X and Y for the empty space
		Spacer(int32_t sizeX, int32_t sizeY);
		// creates empty void for render
		virtual void onRender() const override {};
	};

	class Label : public Widget
	{
	public:
		
		//Constructor with size abnd text
		Label(glm::ivec2 size, const char * labelText);
		//Constructor with size abnd text X and Y
		Label(int32_t sizeX, int32_t sizeY, const char * labelText);
		
		virtual void onRender() const;
		// override the position as it changes based on text size
		virtual void updatePosition(glm::ivec2& relativePosition) override;
	protected:
		//text for label
		const char * m_text;
		//text position
		glm::ivec2 m_textPosition;
	};

	class Button : public Label
	{
	public: 
		//constructor uses  position x & y, button text and callback function 
		 Button(int32_t x, int32_t y, const char * buttonText, std::function<void(void)> onClick) :
		 	//uses label constructor
		 	Label(x, y, buttonText),
		 	// calls callback function on Click
		 	m_callback(onClick)
		 {}
		 //constructor uses  size, button text and callback function 
		 Button(glm::ivec2 size, const char * buttonText, std::function<void(void)> onClick) :
		 	//uses label constructor
		 	Label(size, buttonText),
		 	// calls callback function on Click
		 	m_callback(onClick)
		 {}
		virtual void onRender() const override;
		//mouse pressed gets wraped on call back function
		virtual void onMousePressed(glm::ivec2& mousePosition, int32_t button) override;
	private: 
		//call back function 
		std::function<void(void)> m_callback;
	};

}