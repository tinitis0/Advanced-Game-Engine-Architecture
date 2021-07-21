#pragma once
#include <gtest/gtest.h>

#include "Events/events.h"

const int width = 1024;
const int height = 720;

Engine::WindowResizeEvent re(width, height);

bool OnResizeTrue(Engine::WindowResizeEvent& e)
{
	return true;
}

bool OnResizeFalse(Engine::WindowResizeEvent& e)
{
	return false;
}
