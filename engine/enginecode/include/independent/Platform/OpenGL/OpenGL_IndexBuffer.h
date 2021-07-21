/*! \file OpenGL_IndexBuffer.h */
#pragma once

#include "Rendering/indexBuffer.h"

namespace Engine
{
	/*! \class OpenGL_IndexBuffer 
	* Index Buffer for OpenGL
	*/
	class OpenGL_IndexBuffer : public indexBuffer
	{
	public:
		OpenGL_IndexBuffer(uint32_t * indices, uint32_t count); //!< Constrictor that takes the size and draw count
		virtual ~OpenGL_IndexBuffer(); //!< Destructor
		virtual inline uint32_t getRenderID() const override { return m_OpenGL_ID; } //!< Get Render ID
		virtual inline uint32_t getCount() const override { return m_count; } //!< Get count
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		uint32_t m_count; //!< Effective draw count
	};
}