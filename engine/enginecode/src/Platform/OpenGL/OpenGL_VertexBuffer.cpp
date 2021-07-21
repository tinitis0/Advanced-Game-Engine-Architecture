/*! \file OpenGL_VertexBuffer.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "Platform/OpenGL/OpenGL_VertexBuffer.h"

namespace Engine
{
	Engine::OpenGL_VertexBuffer::OpenGL_VertexBuffer(void * vertices, uint32_t size, VertexBufferLayout layout) : m_layout(layout)
	{
		glCreateBuffers(1, &m_OpenGL_ID); //!< Create buffer based on OpenGL ID
		glBindBuffer(GL_ARRAY_BUFFER, m_OpenGL_ID); //!< Bind buffer based on OpenGL ID
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW); //!< Buffer data based on size and vertices
	}

	Engine::OpenGL_VertexBuffer::~OpenGL_VertexBuffer()
	{
		glDeleteBuffers(1, &m_OpenGL_ID); //!< Delete buffer based on OpenGL ID
	}

	void Engine::OpenGL_VertexBuffer::edit(void * vertices, uint32_t size, uint32_t offset)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_OpenGL_ID); //!< Bind buffer based on OpenGL ID
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices); //!< Edit Range
	}

}
