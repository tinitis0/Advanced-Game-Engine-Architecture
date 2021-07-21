/* \file UILayer.cpp */

#include "UILayer.h"

UILayer::UILayer(const char * name) : Layer(name)
{
	auto& window = Application::getInstance().getWindow();

	Free2DParams camParams;
	
	camParams.width = window->getWidth();
	camParams.height = window->getHeight();
	camParams.top = window->getHeight();
	camParams.right = window->getWidth();

	m_camera.reset(new Free2dOrthographicCamera(camParams));


	m_swu["u_projection"] = static_cast<void*>(glm::value_ptr(m_camera->getCamera().projection)); //!< Upload Projection Data ;
	m_swu["u_view"] = static_cast<void*>(glm::value_ptr(m_camera->getCamera().view));
	//m_swu["u_view"] = std::pair<shaderDataType, void *>(shaderDataType::Mat4, static_cast<void *>(glm::value_ptr(m_camera->getCamera().view)));
	//m_swu["u_projection"] = std::pair<shaderDataType, void *>(shaderDataType::Mat4, static_cast<void *>(glm::value_ptr(m_camera->getCamera().projection)));

	m_quads.push_back(Quad::createCentreHalfExtents({ 450.f, 400.f }, { 100.f, 100.f }));
	m_quads.push_back(Quad::createCentreHalfExtents({ 700.f, 100.f }, { 50.f, 50.f }));
}

void UILayer::onRender()
{

	RendererCommon::actionCommand(RendererCommon::setDepthTestDisable);
	RendererCommon::actionCommand(RendererCommon::setBlendDisabled);

	Renderer2D::begin(m_swu);

	Renderer2D::submit(m_quads[0], { 0.2f,0.6f,0.4f,0.5f });
	Renderer2D::submit(m_quads[1], { 0.8f,0.2f,0.4f,1.0f }, 45.f, true);

	Renderer2D::end();
}
