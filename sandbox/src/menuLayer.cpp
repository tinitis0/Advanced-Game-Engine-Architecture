/* \file menuLayer.cpp */
#include "menuLayer.h"


MenuLayer::MenuLayer(const char * name) : Layer(name)
{
	auto& window = Application::getInstance().getWindow();
	rManager = Application::getInstance().getRM();

	Free2DParams  m_params;
	m_params.width = window->getWidth();
	m_params.height = window->getHeight();

	m_camera.reset(new Free2dOrthographicCamera(m_params));


	m_swu["u_projection"] = static_cast<void*>(glm::value_ptr(m_camera->getCamera().projection)); //!< Upload Projection Data ;
	m_swu["u_view"] = static_cast<void*>(glm::value_ptr(m_camera->getCamera().view));//!< upload view data

	HorizontalContainer top, middle, bottom; //!< containers

	top.addWidget<Spacer>(10, 20); //!< space at top container
	top.addWidget<Label>(100, 100, ""); //!< label at top container

    bottom.addWidget<Button>(400, 50, "", []() {Logger::info("Button 1 is pressed"); });//!< button at bottom container
	bottom.addWidget<Spacer>(500, 10);//!< space at bottom container
	bottom.addWidget<Button>(400, 50, "", []() {Logger::info("Button 2 is pressed"); });//!< button at bottom container



	m_window.addContainer(top); //!< add top container to window	
	m_window.addContainer(middle);//!< add middle container  to window
	m_window.addContainer(bottom);//!< add bottom container  to window

	m_window.show(); //!< show window

}

void MenuLayer::onRender()
{


	switch (m_state)
	{
	case MenuState::Activating:
		m_state = MenuState::Active;
		break;
	case MenuState::Deactivating:
		m_state = MenuState::Inactive;
		break;	
	}

	if (m_state == MenuState::Active)
	{
		RendererCommon::actionCommand(RendererCommon::setDepthTestDisable);
		RendererCommon::actionCommand(RendererCommon::setBlendEnabled);
		//RendererCommon::actionCommand(RendererCommon::setAlphaBlenFunc);
		
		Renderer2D::begin(m_swu);
		m_window.onRender();
		Renderer2D::end();
	}

}

void MenuLayer::onKeyPressed(KeyPressed & e)
{
	
	switch (e.getKeyCode())
	{
	case NG_KEY_G:
		m_state = MenuState::Activating;
		Logger::info("Activating!");
		break;
	case NG_KEY_H:
		m_state = MenuState::Deactivating;
		break;
	}

	if (m_state == MenuState::Active) e.handle(true);
}

void MenuLayer::onMouseReleased(MouseReleased & e)
{
	glm::ivec2 mousePos = InputPoller::getMousePos();
	m_window.onMouseReleased(mousePos, e.getButton());
}

void MenuLayer::onMousePressed(MousePressed & e)
{
	glm::ivec2 mousePos = InputPoller::getMousePos();
	m_window.onMousePressed(mousePos, e.getButton());
}
void MenuLayer::onMouseMove(MouseMoved & e)
{
	glm::ivec2 mousePos = e.getPos();
	m_window.onMouseMoved(mousePos);
}