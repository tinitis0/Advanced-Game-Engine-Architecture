#include "eventTests.h"

TEST(Events, ResizeConstructor){
	Engine::WindowResizeEvent e(800, 600);

	int32_t width1 = e.getWidth();
	int32_t height1 = e.getHeight();

	auto size = e.getSize();
	
	int32_t width2 = size.x;
	int32_t height2 = size.y;

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();
	Engine::EventType staticType = e.getStaticType();

	EXPECT_EQ(width1, 800);
	EXPECT_EQ(width2, 800);
	EXPECT_EQ(height1, 600);
	EXPECT_EQ(height2, 600);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(e.inCategory(Engine::EventCategory::EventCategoryWindow));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::WindowResize);
}

TEST(Events, WindowMoveConstructor)
{
	Engine::WindowMoveEvent e(200, 400);

	int32_t positionX = e.getPositionX();
	int32_t positionY = e.getPositionY();

	auto pos = e.getPos();

	int32_t positionX_2 = pos.x;
	int32_t positionY_2 = pos.y;

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();
	Engine::EventType staticType = e.getStaticType();
	
	EXPECT_EQ(positionX, 200);
	EXPECT_EQ(positionY, 400);
	EXPECT_EQ(positionX_2, 200);
	EXPECT_EQ(positionY_2, 400);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(e.inCategory(Engine::EventCategory::EventCategoryWindow));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::WindowMoved);
}


TEST(Events, MouseMoveConstructor)
{
	Engine::MouseMoved e(650, 460);

	int32_t positionX = e.getPositionX();
	int32_t positionY = e.getPositionY();

	auto pos = e.getPos();

	int32_t positionX_2 = pos.x;
	int32_t positionY_2 = pos.y;

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();
	Engine::EventType staticType = e.getStaticType();

	EXPECT_EQ(positionX, 650);
	EXPECT_EQ(positionY, 460);
	EXPECT_EQ(positionX_2, 650);
	EXPECT_EQ(positionY_2, 460);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryMouse | Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(e.inCategory(Engine::EventCategory::EventCategoryMouse));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::MouseMoved);
}

TEST(Events, MouseScrollConstructor)
{
	Engine::MouseScroll e(0, 1);

	double offsetX = e.getOffsetX();
	double offsetY = e.getOffsetY();

	auto offset = e.getOffset();

	double offsetX_2 = offset.x;
	double offsetY_2 = offset.y;

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();
	Engine::EventType staticType = e.getStaticType();

	EXPECT_EQ(offsetX, 0);
	EXPECT_EQ(offsetY, 1);
	EXPECT_EQ(offsetX_2, 0);
	EXPECT_EQ(offsetY_2, 1);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryMouse | Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(e.inCategory(Engine::EventCategory::EventCategoryMouse));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::MouseScrolled);
}

TEST(Events, CloseEventCategory) {
	Engine::windowCloseEvent e;

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();
	Engine::EventType staticType = e.getStaticType();

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(e.inCategory(Engine::EventCategory::EventCategoryWindow));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::WindowClose);
}

TEST(Events, FocusEventCategory) {
	Engine::WindowFocus e;

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();
	Engine::EventType staticType = e.getStaticType();

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(e.inCategory(Engine::EventCategory::EventCategoryWindow));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::WindowFocus);
}

TEST(Events, KeyPressEventConstructor) {
	Engine::KeyPressed e(4, true);

	auto key = e.getKeyCode();
	auto repeat = e.getRepeatCount();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();
	Engine::EventType staticType = e.getStaticType();

	EXPECT_EQ(key, 4);
	EXPECT_EQ(repeat, true);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryKeyboard | Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(e.inCategory(Engine::EventCategory::EventCategoryKeyboard));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::KeyPressed);
}

TEST(Events, KeyReleaseEventConstructor) {
	Engine::KeyReleased e(4);

	auto key = e.getKeyCode();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();
	Engine::EventType staticType = e.getStaticType();

	EXPECT_EQ(key, 4);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryKeyboard | Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(e.inCategory(Engine::EventCategory::EventCategoryKeyboard));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::KeyReleased);
}

TEST(Events, KeyTypedEventConstructor) {
	Engine::KeyTyped e(6);

	auto key = e.getKeyCode();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();
	Engine::EventType staticType = e.getStaticType();

	EXPECT_EQ(key, 6);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryKeyboard | Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(e.inCategory(Engine::EventCategory::EventCategoryKeyboard));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::KeyTyped);
}

TEST(Events, MousePressedEventConstructor) {
	Engine::MousePressed e(1);

	auto button = e.getMouseButton();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();
	Engine::EventType staticType = e.getStaticType();

	EXPECT_EQ(button, 1);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryMouse | Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(e.inCategory(Engine::EventCategory::EventCategoryMouse));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::MouseButtonPressed);
}

TEST(Events, MouseReleaseEventConstructor) {
	Engine::MouseReleased e(1);

	auto button = e.getMouseButton();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();
	Engine::EventType staticType = e.getStaticType();

	EXPECT_EQ(button, 1);
	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryMouse | Engine::EventCategory::EventCategoryInput);
	EXPECT_TRUE(e.inCategory(Engine::EventCategory::EventCategoryMouse));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::MouseButtonReleased);
}