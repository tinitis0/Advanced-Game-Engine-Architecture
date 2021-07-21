/*! \file indexBuffer.h */
#pragma once

#include <cstdint>

namespace Engine
{
	/*! \class indexBuffer 
	* API Agnostic index buffer
	*/
	class indexBuffer
	{
	public:
		virtual ~indexBuffer() = default; //!< Destructor
		virtual inline uint32_t getRenderID() const = 0; //!< Get Render ID
		virtual inline uint32_t getCount() const = 0; //!< Get count

		static indexBuffer* create(uint32_t * indices, uint32_t count); //!< Create that takes the count and indices
	};
}