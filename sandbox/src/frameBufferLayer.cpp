#include "frameBufferLayer.h"
#include "EnTTLayer.h"

frameBufferLayer::frameBufferLayer(const char * name) : Layer(name)
{
		auto& window = Application::getInstance().getWindow();


#pragma region Framebuffers

	FrameBufferLayout FBlayout = { { AttachmentType::Colour, true}, {AttachmentType::Depth, false} };
	
	textureTarget.reset(FrameBuffer::create({ window->getWidth(), window->getHeight() }, FBlayout));
	defaultTarget.reset(FrameBuffer::createDefault());

	Free2DParams camParams;
	camParams.width = window->getWidth();
	camParams.height = window->getHeight();
	camParams.top = 0;
	camParams.bottom = window->getHeight();

	m_camera2D.reset(new Free2dOrthographicCamera(camParams));

	m_swu2D["u_projection"] = static_cast<void*>(glm::value_ptr(m_camera2D->getCamera().projection)); //!< Upload Projection Data ;
	m_swu2D["u_view"] = static_cast<void*>(glm::value_ptr(m_camera2D->getCamera().view));

	glm::vec2 screen( glm::vec2(window->getWidth(), window->getHeight() ) * 0.5f);
	m_screenQuad = Quad::createCentreHalfExtents(screen, screen);



#pragma endregion

}

void frameBufferLayer::onRender()
{
	defaultTarget->use();

	RendererCommon::actionCommand(RendererCommon::setDepthTestDisable);
	RendererCommon::actionCommand(RendererCommon::setBlendDisabled);
	
	Renderer2D::begin(m_swu2D);

	Renderer2D::submit(m_screenQuad, textureTarget->getTarget(0));

	Renderer2D::end();

	textureTarget->use();
}
