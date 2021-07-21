#pragma once

#include "Rendering/frameBuffer.h"
#include "Platform/OpenGL/OpenGL_RenderBuffer.h"

namespace Engine
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer() { m_ID = 0; };
		OpenGLFrameBuffer(glm::ivec2 size, FrameBufferLayout layout);
		~OpenGLFrameBuffer();
		void use() override; //!< Bind framebuffer
		void onResize(WindowResizeEvent& e) override {};
		uint32_t getID() override { return m_ID; }
		std::shared_ptr<Textures> getTarget(uint32_t index) override;
	protected:
		uint32_t m_ID; //!< ID
	};
}