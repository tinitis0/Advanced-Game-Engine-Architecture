#pragma once

// entry point
#include "include/independent/core/entrypoint.h"
#include "engine.h"
#include "UILayer.h"
#include "EnTTLayer.h"
#include "frameBufferLayer.h"
#include "imGUILayer.h"

class engineApp : public Engine::Application
{
public:
	engineApp(Engine::ApplicationProps props);
	~engineApp() override;
private:

};
