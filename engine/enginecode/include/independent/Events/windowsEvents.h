/*! \file windowsEvents.h */

#pragma once

#include "Events/Event.h"
#include "include/independent/Include.h"

namespace Engine
{

	/*!
	* \class WindowCloseEvent
	*/
	class windowCloseEvent : public Events
	{
	public:
		static EventType getStaticType()
		{
			return EventType::WindowClose; 
		} //!< Return static type

		virtual inline EventType getEventType() const override 
		{ 
			return EventType::WindowClose; 
		} //!< EventType WindowClose
		
		virtual int32_t getCategoryFlags() const override
		{
			return EventCategoryWindow;
		} //!< Under category window
	};

	/*!
	* \class WindowResizeEvent
	*/

	class WindowResizeEvent : public Events
	{
	public:
		WindowResizeEvent(int32_t width, int32_t height) : m_width(width), m_height(height) {} //!< Resize of Window

		static EventType getStaticType()
		{
			return EventType::WindowResize;
		}
		
		virtual inline EventType getEventType() const override
		{
			return EventType::WindowResize;
		}
		virtual int32_t getCategoryFlags() const override
		{
			return EventCategoryWindow;
		}

		inline int32_t getWidth() const { return m_width; } //!< Getter for window width
		inline int32_t getHeight() const { return m_height; } //!< Getter for window height
		inline glm::ivec2 getSize() const { return { m_width, m_height }; } //!< Getter for window size (Width & Height)
	private:
		int32_t m_width; //!< Windows width after resize
		int32_t m_height; //!< Windows height after resize
	};

	/*!
	* \class WindowMoveEvent
	*/

	class WindowMoveEvent : public Events
	{
	public:
		WindowMoveEvent(int32_t xPos, int32_t yPos) : m_xPos(xPos), m_yPos(yPos){} //!< Window Moved

		static EventType getStaticType()
		{
			return EventType::WindowMoved;
		} //!< Return class type

		virtual inline EventType getEventType() const override
		{
			return EventType::WindowMoved;
		} //!< EventType WindowMoved

		virtual int32_t getCategoryFlags() const override
		{
			return EventCategoryWindow;
		} //!< Under category window

		inline int32_t getPositionX() const { return m_xPos; } //!< Get position of window X
		inline int32_t getPositionY() const { return m_yPos; } //!< Get position of window X

		inline glm::vec2 getPos() const { return glm::vec2(m_xPos, m_yPos); } //!< Return positions as 1

	private:
		int32_t m_yPos; //!< X Position
		int32_t m_xPos; //!< Y Position
	};

	/*!
	* \class WindowLostFocus
	*/

	class WindowLostFocus : public Events
	{
	public:

		static EventType getStaticType()
		{
			return EventType::WindowLostFocus;
		} //!< Return static type

		virtual inline EventType getEventType() const override
		{
			return EventType::WindowLostFocus;
		} //!< EventType WindowLostFocus

		virtual int32_t getCategoryFlags() const override
		{
			return EventCategoryWindow;
		} //!< Under category window
	};

	/*!
	* \class WindowFocus
	*/

	class WindowFocus : public Events
	{
	public:

		static EventType getStaticType()
		{
			return EventType::WindowFocus;
		} //!< Return static type

		virtual inline EventType getEventType() const override
		{
			return EventType::WindowFocus;
		} //!< EventType WindowFocus

		virtual int32_t getCategoryFlags() const override
		{
			return EventCategoryWindow;
		} //!< Under category window
	};
}