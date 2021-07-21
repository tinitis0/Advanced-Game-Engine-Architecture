/*! \file OpenGL_VertexArray.h */
#pragma once

#include <memory>
#include <vector>
#include "OpenGL_VertexBuffer.h"
#include "OpenGL_IndexBuffer.h"
#include "Rendering/vertexArray.h"

namespace Engine
{
	/*! \class OpenGL_VertexArray */
	class OpenGL_VertexArray : public vertexArray
	{
	public:
		OpenGL_VertexArray(); //!< Constructor
		virtual ~OpenGL_VertexArray(); //!< Destructor
		void addVertexBuffer(const std::shared_ptr<vertexBuffer>& vertexBuffer); //!< Add a vertex buffer
		void setIndexBuffer(const std::shared_ptr<indexBuffer>& indexBuffer); //!< Set an index buffer
		virtual inline uint32_t getRenderID() const { return m_OpenGL_ID; } //!< Getter for RenderID


	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		uint32_t m_vertexAttribIndex = 0; //!< Attribute Index 

	};
}