#pragma once

#include "engine.h"
#include "Platform/Renderer/3D_Renderer.h"
#include "independent/Rendering/frameBuffer.h"
#include "independent/Rendering/SubTexture.h"
#include "Platform/Renderer/RendererCommon.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Engine;

class frameBufferLayer : public Layer
{
public:
	frameBufferLayer(const char * name);
	void onRender() override;
	void onUpdate(float timestep) override {};
	void onKeyPressed(KeyPressed& e) override {};
	void onResize(WindowResizeEvent& e) override {};

private:
	SceneWideUniforms m_swu;


	// Frame Buffers
	std::shared_ptr<FrameBuffer> textureTarget;
	std::shared_ptr<FrameBuffer> defaultTarget;

	// 2D
	SceneWideUniformsCorrect m_swu2D;

	std::shared_ptr<UniformBuffer> camera2D_UBO;
	
	std::shared_ptr<Free2dOrthographicCamera> m_camera2D;
	Quad m_screenQuad;
};
