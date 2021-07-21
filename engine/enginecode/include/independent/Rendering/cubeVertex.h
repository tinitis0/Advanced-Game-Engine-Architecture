#pragma once

/*! \file cubeVertices.h */

#include "Rendering/BufferLayout.h"

namespace Engine
{
	/*! \class cubeVertices */
	class cubeVertex
	{
	public:
		glm::vec3 m_position; //!< Position
		glm::vec3 m_normal; //!< Colour
		glm::vec2 m_UV; //!< UV
		cubeVertex() : m_position(glm::vec3(0.f)), m_normal(glm::vec3(0.f)), m_UV(glm::vec2(0.f)) {} //!< Constructor that initialises position, normal & UV to 0
		cubeVertex(const glm::vec3& pos, const glm::vec3& norm, const glm::vec2& UV) : m_position(pos), m_normal(norm), m_UV(UV) {} //!< Constructor
		static VertexBufferLayout getLayout() { return s_layout; } //!< Getter function for the static layout
	private:
		static VertexBufferLayout s_layout; //!< Static Buffer Layout
	};
}