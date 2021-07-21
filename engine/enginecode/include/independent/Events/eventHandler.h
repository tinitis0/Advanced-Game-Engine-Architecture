/*! \file eventHandler.h */
#pragma once

#include "events.h"
#include <functional>

namespace Engine
{
	/*!
	* \class eventHandler
	*/
	class eventHandler
	{
	public:
		// Window
		void setOnCloseCallBack(const std::function<bool(windowCloseEvent&)>& fn) { m_onCloseFunc = fn; } //!< Setter for m_onCloseFunc
		void setOnResizeCallBack(const std::function<bool(WindowResizeEvent&)>& fn) { m_onResizeFunc = fn; } //!< Setter for m_onResizeFunc
		void setOnFocusCallBack(const std::function<bool(WindowFocus&)>& fn) { m_onFocusFunc = fn; } //!< Setter for m_onFocusFunc
		void setOnLostFocusCallBack(const std::function<bool(WindowLostFocus&)>& fn) { m_onLostFocusFunc = fn; } //!< Setter for m_onLostFocusFunc
		void setOnWinMoveCallBack(const std::function<bool(WindowMoveEvent&)>& fn) { m_onWinMoveFunc = fn; } //!< Setter for m_onWinMoveFunc
		// Keyboard
		void setOnKeyPressedCallBack(const std::function<void(KeyPressed&)>& fn) { m_onKeyPressedFunc = fn; } //!< Setter for m_onKeyPressedFunc
		void setOnKeyReleasedCallBack(const std::function<bool(KeyReleased&)>& fn) { m_onKeyReleasedFunc = fn; } //!< Setter for m_onKeyReleasedFunc
		void setOnKeyTypedCallBack(const std::function<bool(KeyTyped&)>& fn) { m_onKeyTypedFunc = fn; } //!< Setter for m_onKeyTypedFunc
		// Mouse
		void setOnMousePressedCallBack(const std::function<bool(MousePressed&)>& fn) { m_onMousePressedFunc = fn; } //!< Setter for m_onMousePressedFunc
		void setOnMouseReleasedCallBack(const std::function<bool(MouseReleased&)>& fn) { m_onMouseReleasedFunc = fn; } //!< Setter for m_onMouseReleasedFunc
		void setOnMouseMovedCallBack(const std::function<bool(MouseMoved&)>& fn) { m_onMouseMovedFunc = fn; } //!< Setter for m_onMouseMovedFunc
		void setOnMouseScrollCallBack(const std::function<bool(MouseScroll&)>& fn) { m_onMouseScrollFunc = fn; } //!< Setter for m_onMouseScrollFunc
		
		// Window
		std::function<bool(windowCloseEvent&)>& getOnCloseCallBack() { return m_onCloseFunc; } //!< Getter for m_onCloseFunc
		std::function<bool(WindowResizeEvent&)>& getOnResizeCallBack() { return m_onResizeFunc; } //!< Getter for m_onResizeFunc
		std::function<bool(WindowFocus&)>& getOnFocusCallBack() { return m_onFocusFunc; } //!< Getter for m_onFocusFunc
		std::function<bool(WindowLostFocus&)>& getOnLostFocusCallBack() { return m_onLostFocusFunc; } //!< Getter for m_onLostFocusFunc
		std::function<bool(WindowMoveEvent&)>& getOnWinMoveCallBack() { return m_onWinMoveFunc; } //!< Getter for m_onWinMoveFunc
		// Keyboard
		std::function<void(KeyPressed&)>& getOnKeyPressedCallBack() { return m_onKeyPressedFunc; } //!< Getter for m_onWinMoveFunc
		std::function<bool(KeyReleased&)>& getOnKeyReleasedCallBack() { return m_onKeyReleasedFunc; } //!< Getter for m_onWinMoveFunc
		std::function<bool(KeyTyped&)>& getOnKeyTypedCallBack() { return m_onKeyTypedFunc; } //!< Getter for m_onWinMoveFunc
		// Mouse
		std::function<bool(MousePressed&)>& getOnMousePressedCallBack() { return m_onMousePressedFunc; } //!< Getter for m_onMousePressedFunc
		std::function<bool(MouseReleased&)>& getOnMouseReleasedCallBack() { return m_onMouseReleasedFunc; } //!< Getter for m_onKeyReleasedFunc
		std::function<bool(MouseMoved&)>& getOnMouseMovedCallBack() { return m_onMouseMovedFunc; } //!< Getter for m_onMouseMovedFunc
		std::function<bool(MouseScroll&)>& getOnMouseScrollCallBack() { return m_onMouseScrollFunc; } //!< Getter for m_onWinMoveFunc
	
	private:
		// Window
		std::function<bool(windowCloseEvent&)> m_onCloseFunc = std::bind(&eventHandler::defaultOnClose, this, std::placeholders::_1); //!< Variable which holds bool function "defaultOnClose"
		std::function<bool(WindowResizeEvent&)> m_onResizeFunc = std::bind(&eventHandler::defaultOnResize, this, std::placeholders::_1); //!< Variable which holds bool function "defaultOnResize"
		std::function<bool(WindowFocus&)> m_onFocusFunc = std::bind(&eventHandler::defaultOnFocus, this, std::placeholders::_1); //!< Variable which holds bool function "defaultOnFocus"
		std::function<bool(WindowLostFocus&)> m_onLostFocusFunc = std::bind(&eventHandler::defaultOnLostFocus, this, std::placeholders::_1); //!< Variable which holds bool function "defaultOnLostFocus"
		std::function<bool(WindowMoveEvent&)> m_onWinMoveFunc = std::bind(&eventHandler::defaultOnMove, this, std::placeholders::_1); //!< Variable which holds bool function "defaultOnMove"
		// Keyboard
		std::function<void(KeyPressed&)> m_onKeyPressedFunc = std::bind(&eventHandler::defaultOnKeyPressed, this, std::placeholders::_1); //!< Variable which holds bool function "defaultOnKeyPressed"
		std::function<bool(KeyReleased&)> m_onKeyReleasedFunc = std::bind(&eventHandler::defaultOnKeyReleased, this, std::placeholders::_1); //!< Variable which holds bool function "defaultOnKeyReleased"
		std::function<bool(KeyTyped&)> m_onKeyTypedFunc = std::bind(&eventHandler::defaultOnKeyTyped, this, std::placeholders::_1); //!< Variable which holds bool function "defaultOnKeyTyped"
		// Mouse
		std::function<bool(MousePressed&)> m_onMousePressedFunc = std::bind(&eventHandler::defaultOnMousePressed, this, std::placeholders::_1); //!< Variable which holds bool function "defaultOnMousePressed"
		std::function<bool(MouseReleased&)> m_onMouseReleasedFunc = std::bind(&eventHandler::defaultOnMouseReleased, this, std::placeholders::_1); //!< Variable which holds bool function "defaultOnMouseReleased"
		std::function<bool(MouseMoved&)> m_onMouseMovedFunc = std::bind(&eventHandler::defaultOnMouseMoved, this, std::placeholders::_1); //!< Variable which holds bool function "defaultOnMoved"
		std::function<bool(MouseScroll&)> m_onMouseScrollFunc = std::bind(&eventHandler::defaultOnMouseScroll, this, std::placeholders::_1); //!< Variable which holds bool function "defaultOnScroll"
		
		//Window Bools
		bool defaultOnClose(windowCloseEvent&) { return false; } //!< Bool which returns false
		bool defaultOnResize(WindowResizeEvent&) { return false; } //!< Bool which returns false
		bool defaultOnFocus(WindowFocus&) { return false; } //!< Bool which returns false
		bool defaultOnLostFocus(WindowLostFocus&) { return false; } //!< Bool which returns false
		bool defaultOnMove(WindowMoveEvent&) { return false; } //!< Bool which returns false
		// Keyboard Bools
		bool defaultOnKeyPressed(KeyPressed&) { return false; } //!< Bool which returns false
		bool defaultOnKeyReleased(KeyReleased&) { return false; } //!< Bool which returns false
		bool defaultOnKeyTyped(KeyTyped&) { return false; }
		// Mouse Bools
		bool defaultOnMousePressed(MousePressed&) { return false; } //!< Bool which returns false
		bool defaultOnMouseReleased(MouseReleased&) { return false; } //!< Bool which returns false
		bool defaultOnMouseMoved(MouseMoved&) { return false; } //!< Bool which returns false
		bool defaultOnMouseScroll(MouseScroll&) { return false; } //!< Bool which returns false
	};
}