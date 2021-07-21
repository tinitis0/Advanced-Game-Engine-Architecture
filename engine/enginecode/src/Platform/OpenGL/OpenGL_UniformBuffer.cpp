/*! \file OpenGL_UniformBuffer.cpp  */

#include "engine_pch.h"
#include "Platform/OpenGL/OpenGL_UniformBuffer.h"
#include <glad/glad.h>

namespace Engine
{
	uint32_t OpenGL_UniformBuffer::s_blockNumber = 0; //!< Initailsing the static blockNumber to 0
	OpenGL_UniformBuffer::OpenGL_UniformBuffer(const UniformBufferLayout & layout)
	{
		m_blockNumber = s_blockNumber; //!< m_blocknumber is the static block number
		s_blockNumber++; //!< Increase static blockNumber by 1
		
		m_layout = layout;
		glGenBuffers(1, &m_RenderID); //!< Generate Buffer (Camera UBO)
		glBindBuffer(GL_UNIFORM_BUFFER, m_RenderID); //!< Bind Buffer UBO
		glBufferData(GL_UNIFORM_BUFFER, m_layout.getStride(), nullptr, GL_DYNAMIC_DRAW); //!< Sending buffer the data
		glBindBufferRange(GL_UNIFORM_BUFFER, m_blockNumber, m_RenderID, 0, m_layout.getStride()); //!< Buffer Range Binded
	
		for (auto& element : m_layout)
		{
			m_uniformChache[element.m_name] = std::pair<uint32_t, uint32_t>(element.m_offSet, element.m_size); //!< Filling in cache with the elements size and offset
		}
	}

	OpenGL_UniformBuffer::~OpenGL_UniformBuffer()
	{
		glDeleteBuffers(1, &m_RenderID); //!< Delete the buffer
	}

	void OpenGL_UniformBuffer::attachShaderBlock(const std::shared_ptr<Shader>& shader, const char * blockName)
	{
		uint32_t blockIndex = glGetUniformBlockIndex(shader->getRenderID(), blockName); //!< Binding shader
		glUniformBlockBinding(shader->getRenderID(), blockIndex, m_blockNumber); //!< Bound to flat colour shader
	}

	void OpenGL_UniformBuffer::uploadData(const char * uniformName, void * data)
	{
		auto& pair = m_uniformChache[uniformName]; //!< std::pair uint32_t
		glBindBuffer(GL_UNIFORM_BUFFER, m_RenderID); //!< Bind UBO
		glBufferSubData(GL_UNIFORM_BUFFER, pair.first, pair.second, data); //!< Uploading Data
	}
}