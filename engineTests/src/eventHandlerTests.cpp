/*! \file eventHandlerTests.h */
#include "eventHandlerTests.h"
#include "Platform/GLFW/GLFWCodes.h"

TEST(EventHandler, onClose) {

	MockApplication app;

	Engine::windowCloseEvent e;

	bool handledBefore = e.handled();

	auto& onCloseFunctionDefault = app.m_handler.getOnCloseCallBack();
	onCloseFunctionDefault(e);
	
	bool handledDefault = e.handled();

	app.setCloseCallback();
	auto& onCloseFunction = app.m_handler.getOnCloseCallBack();
	
	onCloseFunction(e);

	bool handledAfter = e.handled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onCloseFalse) {

	MockApplication app;

	Engine::windowCloseEvent e;

	bool handledBefore = e.handled();

	auto& onCloseFunctionDefault = app.m_handler.getOnCloseCallBack();
	onCloseFunctionDefault(e);

	bool handledDefault = e.handled();

	app.setCloseFalseCallback();
	auto& onCloseFunction = app.m_handler.getOnCloseCallBack();

	onCloseFunction(e);

	bool handledAfter = e.handled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_EQ(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, false);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onResizeTrue) {

	MockApplication app;

	Engine::WindowResizeEvent e(800, 400);

	bool handledBefore = e.handled();

	auto& onResizeFunctionDefault = app.m_handler.getOnResizeCallBack();
	onResizeFunctionDefault(e);

	bool handledDefault = e.handled();

	app.setResizeCallback();
	auto& onResizeFunction = app.m_handler.getOnResizeCallBack();

	onResizeFunction(e);

	bool handledAfter = e.handled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onMove) {

	MockApplication app;

	Engine::WindowMoveEvent e(400, 600);

	bool handledBefore = e.handled();

	auto& onMoveFunctionDefault = app.m_handler.getOnWinMoveCallBack();
	onMoveFunctionDefault(e);

	bool handledDefault = e.handled();

	app.setMoveCallback();
	auto& onMoveFunction = app.m_handler.getOnWinMoveCallBack();

	onMoveFunction(e);

	bool handledAfter = e.handled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onFocus) {

	MockApplication app;

	Engine::WindowFocus e;

	bool handledBefore = e.handled();

	auto& onFocusFunctionDefault = app.m_handler.getOnFocusCallBack();
	onFocusFunctionDefault(e);

	bool handledDefault = e.handled();

	app.setFocusCallback();
	auto& onFocusFunction = app.m_handler.getOnFocusCallBack();

	onFocusFunction(e);

	bool handledAfter = e.handled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onKeyPress) {

	MockApplication app;

	Engine::KeyPressed e(4, 2);

	bool handledBefore = e.handled();

	auto& onKeyPressFunctionDefault = app.m_handler.getOnKeyPressedCallBack();
	onKeyPressFunctionDefault(e);

	bool handledDefault = e.handled();

	app.setKeyPressCallback();
	auto& onKeyPressFunction = app.m_handler.getOnKeyPressedCallBack();

	onKeyPressFunction(e);

	bool handledAfter = e.handled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onKeyRelease) {

	MockApplication app;

	Engine::KeyReleased e(4);

	bool handledBefore = e.handled();

	auto& onKeyReleaseFunctionDefault = app.m_handler.getOnKeyReleasedCallBack();
	onKeyReleaseFunctionDefault(e);

	bool handledDefault = e.handled();

	app.setKeyReleaseCallback();
	auto& onKeyReleaseFunction = app.m_handler.getOnKeyReleasedCallBack();

	onKeyReleaseFunction(e);

	bool handledAfter = e.handled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onKeyTyped) {

	MockApplication app;

	Engine::KeyTyped e(4);

	bool handledBefore = e.handled();

	auto& onKeyTypedFunctionDefault = app.m_handler.getOnKeyTypedCallBack();
	onKeyTypedFunctionDefault(e);

	bool handledDefault = e.handled();

	app.setKeyTypedCallback();
	auto& onKeyTypedFunction = app.m_handler.getOnKeyTypedCallBack();

	onKeyTypedFunction(e);

	bool handledAfter = e.handled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onMousePressed) {

	MockApplication app;

	Engine::MousePressed e(2);

	bool handledBefore = e.handled();

	auto& onMousePressFunctionDefault = app.m_handler.getOnMousePressedCallBack();
	onMousePressFunctionDefault(e);

	bool handledDefault = e.handled();

	app.setMousePressCallback();
	auto& onMousePressFunction = app.m_handler.getOnMousePressedCallBack();

	onMousePressFunction(e);

	bool handledAfter = e.handled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onMouseRelease) {

	MockApplication app;

	Engine::MouseReleased e(2);

	bool handledBefore = e.handled();

	auto& onMouseReleaseFunctionDefault = app.m_handler.getOnMouseReleasedCallBack();
	onMouseReleaseFunctionDefault(e);

	bool handledDefault = e.handled();

	app.setMouseReleaseCallback();
	auto& onMouseReleaseFunction = app.m_handler.getOnMouseReleasedCallBack();

	onMouseReleaseFunction(e);

	bool handledAfter = e.handled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onMouseScroll) {

	MockApplication app;

	Engine::MouseScroll e(0, 10);

	bool handledBefore = e.handled();

	auto& onMouseScrollFunctionDefault = app.m_handler.getOnMouseScrollCallBack();
	onMouseScrollFunctionDefault(e);

	bool handledDefault = e.handled();

	app.setMouseScrollCallback();
	auto& onMouseScrollFunction = app.m_handler.getOnMouseScrollCallBack();

	onMouseScrollFunction(e);

	bool handledAfter = e.handled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}

TEST(EventHandler, onMouseMove) {

	MockApplication app;

	Engine::MouseMoved e(300, 200);

	bool handledBefore = e.handled();

	auto& onMouseMoveFunctionDefault = app.m_handler.getOnMouseMovedCallBack();
	onMouseMoveFunctionDefault(e);

	bool handledDefault = e.handled();

	app.setMouseMoveCallback();
	auto& onMouseMoveFunction = app.m_handler.getOnMouseMovedCallBack();

	onMouseMoveFunction(e);

	bool handledAfter = e.handled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}