/*! \file OpenGL_VertexBuffer.h */
#pragma once
#include "Rendering/BufferLayout.h"
#include "Rendering/vertexBuffer.h"

namespace Engine
{
	/*! \class OpenGL_VertexBuffer */
	class OpenGL_VertexBuffer : public vertexBuffer
	{
	public:
		OpenGL_VertexBuffer(void* vertices, uint32_t size, VertexBufferLayout layout); //!< Constructor with data
		~OpenGL_VertexBuffer(); //!< Destructor
		void edit(void* vertices, uint32_t size, uint32_t offset); //!< Edit the vertex buffer
		inline const uint32_t getRenderID() const override { return m_OpenGL_ID; } //!< Getter for OpenGL ID
		inline const VertexBufferLayout& getLayout() const { return m_layout; } //!< Getter for layout
	private:
		uint32_t m_OpenGL_ID; //!< Render ID e.g. cubeVBO
		VertexBufferLayout m_layout; //!< Buffer Layout
	};

}