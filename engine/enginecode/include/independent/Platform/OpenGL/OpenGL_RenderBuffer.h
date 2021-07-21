#pragma once

#include "Rendering/RenderBuffer.h"

namespace Engine
{
	class OpenGL_RenderBuffer : public RenderBuffer
	{
	public:
		OpenGL_RenderBuffer() { m_ID = 0; };
		OpenGL_RenderBuffer(AttachmentType type, glm::ivec2 size);
		uint32_t getID() override { return m_ID; }

	protected:
		uint32_t m_ID; //!< ID
	};
}