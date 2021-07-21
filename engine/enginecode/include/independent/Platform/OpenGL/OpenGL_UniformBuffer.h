/*! \file OpenGL_UniformBuffer.h*/
#pragma once
#include "Rendering/UniformBuffer.h"

namespace Engine
{
	/*! \class OpenGL_UniformBuffer */
	class OpenGL_UniformBuffer : public UniformBuffer
	{
	public:
		OpenGL_UniformBuffer(const UniformBufferLayout& layout); //!< Constructor
		~OpenGL_UniformBuffer(); //!< Destructor
		inline uint32_t getRenderID() override { return m_RenderID; } //!< Getter for RenderID
		inline UniformBufferLayout getLayout() override { return m_layout; } //!< Getter for layout
		void attachShaderBlock(const std::shared_ptr<Shader>& shader, const char * blockName) override; //!< Attach a Shader
		void uploadData(const char * uniformName, void* data) override; //!< Upload Data
	private:
		uint32_t m_RenderID; //!< Render ID
		static uint32_t s_blockNumber; //!< Static block number 
	};
}