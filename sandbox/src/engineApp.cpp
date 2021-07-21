/** \file engineApp.cpp
*/

#include "engineApp.h"

engineApp::engineApp(Engine::ApplicationProps props) : Application(props)
{
	m_layerStack.push(new EnTTLayer("EnTT Layer"));
	m_layerStack.push(new UILayer("UI Layer"));
	m_layerStack.push(new frameBufferLayer("FB Layer"));
	
	
}

engineApp::~engineApp()
{

}

Engine::Application* Engine::startApplication()
{
	ApplicationProps props;
	props.winProps.title = "Sandbox App";
	props.winProps.width = 900;
	props.winProps.height = 800;

	return new engineApp(props);
}