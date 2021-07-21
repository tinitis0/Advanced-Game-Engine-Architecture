#pragma once
/*! \file evenHandlerTests.h */
#include <gtest/gtest.h>

#include "Events/events.h"
#include "Events/eventHandler.h"

/*! \class MockApplication */
class MockApplication
{
public:
	void setCloseCallback()
	{
		m_handler.setOnCloseCallBack(std::bind(&MockApplication::onClose, this, std::placeholders::_1));
	}

	void setCloseFalseCallback()
	{
		m_handler.setOnCloseCallBack(std::bind(&MockApplication::onCloseFalse, this, std::placeholders::_1));
	}

	void setResizeCallback()
	{
		m_handler.setOnResizeCallBack(std::bind(&MockApplication::onResizeTrue, this, std::placeholders::_1));
	}

	void setResizeFalseCallback()
	{
		m_handler.setOnResizeCallBack(std::bind(&MockApplication::onResizeFalse, this, std::placeholders::_1));
	}

	void setMoveCallback()
	{
		m_handler.setOnWinMoveCallBack(std::bind(&MockApplication::onMove, this, std::placeholders::_1));
	}

	void setFocusCallback()
	{
		m_handler.setOnFocusCallBack(std::bind(&MockApplication::onFocus, this, std::placeholders::_1));
	}
	
	void setKeyPressCallback()
	{
		m_handler.setOnKeyPressedCallBack(std::bind(&MockApplication::onKeyPress, this, std::placeholders::_1));
	}

	void setKeyReleaseCallback()
	{
		m_handler.setOnKeyReleasedCallBack(std::bind(&MockApplication::onKeyRelease, this, std::placeholders::_1));
	}

	void setKeyTypedCallback()
	{
		m_handler.setOnKeyTypedCallBack(std::bind(&MockApplication::onKeyTyped, this, std::placeholders::_1));
	}

	void setMousePressCallback()
	{
		m_handler.setOnMousePressedCallBack(std::bind(&MockApplication::onMousePressed, this, std::placeholders::_1));
	}

	void setMouseReleaseCallback()
	{
		m_handler.setOnMouseReleasedCallBack(std::bind(&MockApplication::onMouseRelease, this, std::placeholders::_1));
	}

	void setMouseScrollCallback()
	{
		m_handler.setOnMouseScrollCallBack(std::bind(&MockApplication::onMouseScroll, this, std::placeholders::_1));
	}

	void setMouseMoveCallback()
	{
		m_handler.setOnMouseMovedCallBack(std::bind(&MockApplication::onMouseMove, this, std::placeholders::_1));
	}

	Engine::eventHandler m_handler;
private:

	bool onClose(Engine::windowCloseEvent& e)
	{
		e.handle(true);
		return e.handled();
	};

	bool onCloseFalse(Engine::windowCloseEvent& e)
	{
		e.handle(false);
		return e.handled();
	};

	bool onResizeTrue(Engine::WindowResizeEvent& e)
	{
		e.handle(true);
		return e.handled();
	};

	bool onResizeFalse(Engine::WindowResizeEvent& e)
	{
		e.handle(false);
		return e.handled();
	};

	bool onMove(Engine::WindowMoveEvent& e)
	{
		e.handle(true);
		return e.handled();
	};

	bool onFocus(Engine::WindowFocus& e)
	{
		e.handle(true);
		return e.handled();
	};

	bool onKeyPress(Engine::KeyPressed& e)
	{
		e.handle(true);
		return e.handled();
	};

	bool onKeyRelease(Engine::KeyReleased& e)
	{
		e.handle(true);
		return e.handled();
	};

	bool onKeyTyped(Engine::KeyTyped& e)
	{
		e.handle(true);
		return e.handled();
	};

	bool onMousePressed(Engine::MousePressed& e)
	{
		e.handle(true);
		return e.handled();
	};

	bool onMouseRelease(Engine::MouseReleased& e)
	{
		e.handle(true);
		return e.handled();
	};

	bool onMouseScroll(Engine::MouseScroll& e)
	{
		e.handle(true);
		return e.handled();
	};

	bool onMouseMove(Engine::MouseMoved& e)
	{
		e.handle(true);
		return e.handled();
	};
};