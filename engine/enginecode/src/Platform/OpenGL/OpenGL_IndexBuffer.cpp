/*! \file OpenGL_IndexBuffer.cpp */

#include "engine_pch.h"
#include "Platform/OpenGL/OpenGL_IndexBuffer.h"
#include <glad/glad.h>

namespace Engine
{
	OpenGL_IndexBuffer::OpenGL_IndexBuffer(uint32_t * indices, uint32_t count) : m_count(count)
	{
		glCreateBuffers(1, &m_OpenGL_ID); //!< Create index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_OpenGL_ID); //!< Bind buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_STATIC_DRAW); //!< Sending data to GPU (Indices)
	}
	OpenGL_IndexBuffer::~OpenGL_IndexBuffer()
	{
		glDeleteBuffers(1, &m_OpenGL_ID); //!< Delete Buffer
	}
}