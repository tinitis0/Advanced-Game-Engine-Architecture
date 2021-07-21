/*! \file vertexArray.h */
#pragma once

#include <inttypes.h>
#include <cstdint>
#include "Rendering/BufferLayout.h"
#include "Rendering/indexBuffer.h"
#include "Rendering/vertexBuffer.h"

namespace Engine
{
	/*! \class vertexArray
	* API Agnostic vertex array
	*/
	class vertexArray
	{
	public:
		virtual ~vertexArray() = default; //!< Destructor
		virtual void addVertexBuffer(const std::shared_ptr<vertexBuffer>& vertexBuffer) = 0; //!< Add a vertex buffer
		virtual void setIndexBuffer(const std::shared_ptr<indexBuffer>& indexBuffer) = 0; //!< Set an index buffer
		virtual inline uint32_t getRenderID() const = 0;
		
		inline std::shared_ptr<indexBuffer> getIndexBuffer() { return m_indexBuffer; } //!< Getter for index buffer
		inline std::shared_ptr<vertexBuffer> getVertexBuffer(uint32_t index) { return m_vertexBuffers.at(index); } //!< Getter for vertex buffer
		inline uint32_t getDrawCount() const { if (m_indexBuffer) { m_indexBuffer->getCount(); } else { return 0; } } //!< Getter for draw count
		static vertexArray* create();  //!< Create

	protected:
		std::shared_ptr<indexBuffer> m_indexBuffer; //!< Index Buffer
		std::vector<std::shared_ptr<vertexBuffer>> m_vertexBuffers; //!< Vertex Buffer
	};
}