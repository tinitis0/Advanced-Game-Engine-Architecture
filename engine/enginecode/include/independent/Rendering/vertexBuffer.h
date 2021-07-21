/*! \file vertexBuffer.h */
#pragma once

#include <inttypes.h>
#include <cstdint>
#include "Rendering/BufferLayout.h"

namespace Engine
{
	/*! \class vertexBuffer
	* API Agnostic vertex buffer
	*/
	class vertexBuffer
	{
	public:
		virtual ~vertexBuffer() = default; //!< Destructor
		virtual void edit(void* vertices, uint32_t size, uint32_t offset) = 0; //!< Edit the vertex buffer
		virtual inline const uint32_t getRenderID() const = 0; //!< Getter for OpenGL ID
		virtual inline const VertexBufferLayout& getLayout() const = 0; //!< Getter for layout

		static vertexBuffer* create(void* vertices, uint32_t size, const VertexBufferLayout& layout); //!< Create that takes the count and indices
	};
}
