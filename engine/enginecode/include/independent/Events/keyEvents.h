/*! \file keyEvents.h */

#pragma once

#include "Events/Event.h"
#include "include/independent/Include.h"

namespace Engine
{

	/*!
	* \class KeyEvent
	*/
	class KeyEvent : public Events
	{
	public:
		inline  int32_t getKeyCode() const 
		{ 
			return m_keyCode; //!< Return key pressed
		}

		virtual int32_t getCategoryFlags() const override
		{
			return EventCategoryKeyboard | EventCategoryInput;
		} //!< Under category Keyboard & Input
	
	protected:
		KeyEvent(int32_t keyCode) : m_keyCode(keyCode){}
		int32_t  m_keyCode; //!< Key pressed
	};

	/*!
	* \class KeyPressed
	*/
	class KeyPressed : public KeyEvent
	{
	public:

		KeyPressed(int32_t key, bool repeat) : KeyEvent(key), m_repeatCount(repeat) {} //!< Key pressed and repeat count
		
		inline int32_t getRepeatCount() const
		{
			return m_repeatCount; //!< Repeat Count
		}

		static EventType getStaticType()
		{
			return EventType::KeyPressed; //!< Returns the class type
		}

		virtual inline EventType getEventType() const override
		{
			return EventType::KeyPressed; //!< Returns event type
		}
	private:
		
		bool m_repeatCount; //!< Has the key been repeated
	};

	/*!
	* \class KeyReleased
	*/

	class KeyReleased : public KeyEvent
	{
	public:
		KeyReleased(int32_t key) : KeyEvent(key) {} //!< Key Released
		static EventType getStaticType()
		{
			return EventType::KeyReleased; //!< Returns the class type
		}
		virtual inline EventType getEventType() const override
		{
			return EventType::KeyReleased; //!< Returns the event type
		}
	};

	/*!
	* \class KeyTyped
	*/

	class KeyTyped : public KeyEvent
	{
	public:
		KeyTyped(int32_t key) : KeyEvent(key) {} //!< Key Typed
		static EventType getStaticType()
		{
			return EventType::KeyTyped; //!< Returns class type
		}
		virtual inline EventType getEventType() const override
		{
			return EventType::KeyTyped; //!< Return Event Type
		}
	};
}