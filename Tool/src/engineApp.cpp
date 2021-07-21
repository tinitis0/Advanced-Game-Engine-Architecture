/** \file engineApp.cpp
*/

#include "engineApp.h"

engineApp::engineApp(Engine::ApplicationProps props) : Application(props)
{
	EnTTLayer * enttLayer = new EnTTLayer("EnTT Layer");
	m_layerStack.push(enttLayer);
	//m_layerStack.push(new frameBufferLayer("FB Layer"));
	m_layerStack.push(new imGUILayer("ImGUI Layer", enttLayer));
	//m_layerStack.push(new UILayer("UI Layer"));
	
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