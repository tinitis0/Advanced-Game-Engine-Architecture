#pragma once

/*! \file FCVertex.h */

#include "Rendering/BufferLayout.h"

namespace Engine
{
	/*! \class FCVertex (Flat Colour) */
	class FCVertex
	{
	public:
		glm::vec3 m_position; //!< Position
		uint32_t m_colour; //!< Colour
		FCVertex() : m_position(glm::vec3(0.f)), m_colour(0) {} //!< Constructor that initialises position and colour to 0
		FCVertex(const glm::vec3& pos, const uint32_t col) : m_position(pos), m_colour(col) {} //!< Constructor
		static VertexBufferLayout getLayout() { return s_layout; } //!< Getter function for the static layout
	private:
		static VertexBufferLayout s_layout; //!< Static Buffer Layout
	};
}