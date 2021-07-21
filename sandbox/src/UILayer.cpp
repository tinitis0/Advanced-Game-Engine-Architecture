/* \file UILayer.cpp */

#include "UILayer.h"

UILayer::UILayer(const char * name) : Layer(name)
{
	auto& window = Application::getInstance().getWindow(); //!< Get the window
	rManager = Application::getInstance().getRM(); //!< Get the resource manager

	Free2DParams camParams; //!< 2D camera parameters
	
	camParams.width = window->getWidth(); //!< Set the 2d camera's width
	camParams.height = window->getHeight(); //!< Set the 2D camera's height
	camParams.top = window->getHeight(); //!< Set the top of the 2D camera's view
	camParams.right = window->getWidth(); //!< Set the bottom of the 2D camera's view

	m_camera.reset(new Free2dOrthographicCamera(camParams)); //!< Create the 2D camera

	congratsTex.reset(Textures::create("assets/textures/CongratulationsMessage.png")); //!< Create a texture with the congratulations message picture


	m_swu["u_projection"] = static_cast<void*>(glm::value_ptr(m_camera->getCamera().projection)); //!< Upload Projection Data ;
	m_swu["u_view"] = static_cast<void*>(glm::value_ptr(m_camera->getCamera().view));
	//m_swu["u_view"] = std::pair<shaderDataType, void *>(shaderDataType::Mat4, static_cast<void *>(glm::value_ptr(m_camera->getCamera().view)));
	//m_swu["u_projection"] = std::pair<shaderDataType, void *>(shaderDataType::Mat4, static_cast<void *>(glm::value_ptr(m_camera->getCamera().projection)));

	//!< Push all necessary quads to the quads stack
	m_quads.push_back(Quad::createCentreHalfExtents({ 650.f, 400.f }, { 10.f, 100.f }));
	m_quads.push_back(Quad::createCentreHalfExtents({ 650.f, 500.f }, { 15.f, 2.5f }));
	m_quads.push_back(Quad::createCentreHalfExtents({ 50.f, 650.f }, { 30.f, 10.f }));
	m_quads.push_back(Quad::createCentreHalfExtents({ 50.f, 600.f }, { 30.f, 10.f }));
	m_quads.push_back(Quad::createCentreHalfExtents({ 50.f, 550.f }, { 30.f, 10.f }));
	m_quads.push_back(Quad::createCentreHalfExtents({ 50.f, 500.f }, { 30.f, 10.f }));
	m_quads.push_back(Quad::createCentreHalfExtents({ 50.f, 450.f }, { 30.f, 10.f }));
	m_quads.push_back(Quad::createCentreHalfExtents({ 50.f, 400.f }, { 30.f, 10.f }));
	m_quads.push_back(Quad::createCentreHalfExtents({ 50.f, 350.f }, { 30.f, 10.f }));
	m_quads.push_back(Quad::createCentreHalfExtents({ 50.f, 300.f }, { 30.f, 10.f }));
	m_quads.push_back(Quad::createCentreHalfExtents({ 450.f, 150.f }, { 200.f, 75.f }));
	m_quads.push_back(Quad::createCentreHalfExtents({ 650.f, 400.f }, { 15.f, 105.f }));
}

void UILayer::onRender()
{

	RendererCommon::actionCommand(RendererCommon::setDepthTestDisable); //!< Disable depth testing
	RendererCommon::actionCommand(RendererCommon::setBlendDisabled); //!< Set blending to disabled

	Renderer2D::begin(m_swu); //!< Begin the 2D renderer

	Renderer2D::submit(m_quads[11], { 0.f, 0.f, 0.f, 1.0f }); //!< Outline of the power bar
	Renderer2D::submit(m_quads[0], { 0.2f, 0.6f, 0.4f, 0.5f }); //!< Submit the power bar background
	Renderer2D::submit(m_quads[1], { 3.f, 0.f, 0.f, 1.0f }); //!< Submit the power marker
	

	for (int i = 0; i < rManager->maxStrokes - rManager->strokes; i++) //!< Get the number of available strokes
	{
		Renderer2D::submit(m_quads[i + 2], { 6.f, 3.f, 0.f, 1.0f }); //!< Submit the same number of quads
	}
	if (rManager->finished == true) //!< If the player has finished the game
	{
		Renderer2D::submit(m_quads[10], congratsTex); //!< Submit a quad with the congratulations texture
	}

	//Renderer2D::submit('0', glm::vec2(x, 550.f), advance, glm::vec4(1.f, 1.f, 1.f, 1.f));

	Renderer2D::end(); //!< End the 2D renderer
}

void UILayer::onUpdate(float timestep)
{
	m_quads[1].setTranslate(glm::vec3(650.f, 500.f - rManager->getForce() / 5, 0.f)); //!< Every frame set the power marker to be accurate to the charged up power
}