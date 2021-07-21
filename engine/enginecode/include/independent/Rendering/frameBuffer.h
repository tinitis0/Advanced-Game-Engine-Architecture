#pragma once

#include "Events/events.h"
#include "Textures.h"
#include <vector>
#include "RenderBuffer.h"

namespace Engine
{
	class FrameBufferLayout
	{
	public:
		FrameBufferLayout() {};
		FrameBufferLayout(const std::initializer_list<Attachment>& attachments, uint32_t stride = 0) : m_attachments(attachments) {}
		void addAttachment(AttachmentType type, bool sampled = false) 
		{
			m_attachments.push_back(Attachment(type, sampled));
		}
		std::vector<Attachment>::iterator begin() { return m_attachments.begin(); }
		std::vector<Attachment>::iterator end() { return m_attachments.end(); }
		std::vector<Attachment>::const_iterator begin() const { return m_attachments.begin(); }
		std::vector<Attachment>::const_iterator end() const { return m_attachments.end(); }

	private:
		std::vector<Attachment> m_attachments;
	};

	class FrameBuffer
	{
	public:
		~FrameBuffer() = default;
		virtual void onResize(WindowResizeEvent& e) = 0;
		virtual uint32_t getID() = 0;
		virtual void use() = 0; //!, Bind this framebuffer
		virtual std::shared_ptr<Textures> getTarget(uint32_t index) = 0;

		static FrameBuffer* create(const glm::ivec2& size, const FrameBufferLayout& layout);
		static FrameBuffer* createDefault();
	protected:
		glm::ivec2 m_size; //!< Size of framebuffer
		FrameBufferLayout m_layout; //!< Layout of Framebuffer attahcments
		std::vector<std::shared_ptr<Textures>> m_sampledTargets;
		std::vector<std::shared_ptr<RenderBuffer>> m_nonSampledTargets;
	};

}