/*! \file mouseEvents.h */

#pragma once

#include "Events/Event.h"
#include "include/independent/Include.h"

namespace Engine
{
	/*!
	* \class MouseEvent
	*/

	class MouseEvent : public Events
	{
	public:
		virtual int32_t getCategoryFlags() const override
		{
			return EventCategoryMouse | EventCategoryInput;
		} //!< Under category Keyboard & Input
	};

	/*!
	* \class MousePressed
	*/

	class MousePressed : public  MouseEvent
	{
	public:
		
		inline  int32_t getMouseButton() const
		{
			return m_mouseButton; //!< Return button pressed
		}

		MousePressed(int32_t mouseButton) : m_mouseButton(mouseButton) {} //!< Mouse button Pressed

		static EventType getStaticType()
		{
			return EventType::MouseButtonPressed; //!< Return class type
		}

		virtual inline EventType getEventType() const override
		{
			return EventType::MouseButtonPressed; //!< Return event type
		}

		inline int32_t getButton() const { return m_mouseButton; } //!< Gets the mouse button pressed
	
	private:
		
		int32_t m_mouseButton; //!< Mouse Button
	};

	/*!
	* \class MouseReleased
	*/

	class MouseReleased : public  MouseEvent
	{
	public:

		MouseReleased(int32_t mouseButton) : m_mouseButton(mouseButton) {} //!< Mouse button released
		
		inline  int32_t getMouseButton() const
		{
			return m_mouseButton; //!< Return button pressed
		}

		static EventType getStaticType()
		{
			return EventType::MouseButtonReleased; //!< Return class type
		}

		virtual inline EventType getEventType() const override
		{
			return EventType::MouseButtonReleased; //!< Return event type
		}

		inline int32_t getButton() const { return m_mouseButton; } //!< Gets the mouse button released
	
	private:

		int32_t m_mouseButton; //!< Mouse button
	};

	/*!
	* \class MouseMoved
	*/

	class MouseMoved : public MouseEvent
	{
	public:
		
		MouseMoved(double mouseX, double mouseY) : m_mouseX(mouseX), m_mouseY(mouseY) {} //!< Mouse moved (location)

		static EventType getStaticType()
		{
			return EventType::MouseMoved; //!< Return class type
		}

		virtual inline EventType getEventType() const override
		{
			return EventType::MouseMoved; //!< Return event type
		}


		inline double getPositionX() const { return m_mouseX; } //!< Get position of mouse X
		inline double getPositionY() const { return m_mouseY; } //!< Get position of mouse Y

		inline glm::vec2 getPos() const { return glm::vec2(m_mouseX, m_mouseY); } //!< Return positions as 1

	private:
		double m_mouseX; //!< Mouse X Position
		double m_mouseY; //!< Mouse Y Position 
	};

	/*!
	* \class MouseScrolled
	*/

	class MouseScroll : public MouseEvent
	{
	public:

		MouseScroll(double scrollX, double scrollY) : m_scrollX(scrollX), m_scrollY(scrollY) {} //!< Mouse Scroll Wheel

		static EventType getStaticType()
		{
			return EventType::MouseScrolled; //!< Return class type
		}

		virtual inline EventType getEventType() const override
		{
			return EventType::MouseScrolled; //!< Return event type
		}

		inline double getOffsetX() const { return m_scrollX; } //!< Getter for Y Offset
		inline double getOffsetY() const { return m_scrollY; } //!< Getter for X Offset

		inline glm::vec2 getOffset() const { return glm::vec2(m_scrollX, m_scrollY); } //!< Return positions as 1

	private:
		double m_scrollX; //!< Mouse X Position
		double m_scrollY; //!< Mouse Y Position 
	};
}