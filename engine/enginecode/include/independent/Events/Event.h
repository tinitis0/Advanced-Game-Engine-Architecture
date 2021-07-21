/*! \file event.h */
#pragma once


namespace Engine
{
	/*! \enum EventType
	* An enum for event types within the application
	* Window
	* Key Presses
	* Mouse
	*/

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/*! \enum EvenyCategory
	* Enum for type category
	* Categrories for the events to go under
	*/

	enum EventCategory
	{
		None = 0,
		EventCategoryWindow = 1 << 0,		// Category Window, 00000001
		EventCategoryInput = 1 << 1,		// Caegory Input (Mouse / Keyboard), 00000010
		EventCategoryKeyboard = 1 << 2,		// Category Keyboard, 00000100
		EventCategoryMouse = 1 << 3,		// Category Mouse, 00001000
		EventCategoryMouseButton = 1 << 4  // Category Mouse Button, 00010000
	};

	/*!
	* \class Events
	*/

	class Events
	{
	public:
		
		virtual EventType getEventType() const = 0; //!< Get the event type
		virtual int32_t getCategoryFlags() const = 0; //!< Get category flags for events
		
		inline bool handled() const	//!< Has the event been handled?
		{
			return m_handled; //!< Return boolean m_handled
		}; 

		inline void handle(bool isHandled) 
		{
			m_handled = isHandled; 
		} //!< m_handled is set to bool isHandled

		inline bool inCategory(EventCategory category) const
		{
			return getCategoryFlags() & category;
		}; //!< Check whether the event is within the set
	
	protected:
		bool m_handled = false; //!< Has the event been handled?
	};
}