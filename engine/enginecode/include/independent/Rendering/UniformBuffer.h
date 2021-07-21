/*! \file UniformBuffer.h */
#pragma once

#include "Rendering/BufferLayout.h"
#include "Rendering/Shader.h"

#include <memory>
#include <unordered_map>
#include <ctype.h>


namespace Engine
{
	/*! \class UniformBuffer */
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() = default; //!< Destructor
		virtual uint32_t getRenderID() = 0; //!< Getter for RenderID
		virtual UniformBufferLayout getLayout() = 0; //!< Getter for layout
		virtual void attachShaderBlock(const std::shared_ptr<Shader>& shader, const char * blockName) = 0; //!< Attach a Shader
		virtual void uploadData(const char * uniformName, void* data) = 0; //!< Upload Data
	
		static UniformBuffer* create(const UniformBufferLayout& layout); //!< Create layout
	protected:
		UniformBufferLayout m_layout; //!< Uniform Buffer Layout
		std::unordered_map<const char *, std::pair<uint32_t, uint32_t>> m_uniformChache; //!< Stores uniform names with offset and sizes
		uint32_t m_blockNumber; //!< Block Number for uniform buffer object 
	};
}
