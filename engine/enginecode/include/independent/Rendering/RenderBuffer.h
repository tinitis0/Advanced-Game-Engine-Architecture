#pragma once

#include "glm/glm.hpp"

namespace Engine 
{
	enum class AttachmentType { None, Colour, Depth, Stencil, DepthAndStencil };

	using Attachment = std::pair<AttachmentType, bool>;

	class RenderBuffer
	{
	public:
		virtual ~RenderBuffer() = default;
		virtual uint32_t getID() = 0;

		static RenderBuffer* create(AttachmentType& type, glm::ivec2& size);
	};
}