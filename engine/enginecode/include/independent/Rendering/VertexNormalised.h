#pragma once

/*! \file VertexNormalised.h */

namespace Engine
{
	/*! \class TPVertexNormalised */

	class VertexNormalised
	{
	public:
		glm::vec3 m_position; //!< Position Vec3 Float3
		std::array<int16_t, 3> m_normal; //!< Normal 
		std::array<int16_t, 2> m_UV; //!< UV

		VertexNormalised() : m_position(glm::vec3(0.f)), m_normal({ 0,0,0 }), m_UV({ 0,0 }) {} //!< Constructor
		VertexNormalised(const glm::vec3& pos, const std::array<int16_t, 3>& normal, const std::array<int16_t, 2>& UV) :
			m_position(pos), m_normal(normal), m_UV(UV) {}  //!< Vertex normalised constructor
		static VertexBufferLayout getLayout() { return s_layout; } //!< Getter for layout
	private:
		static VertexBufferLayout s_layout; //!< Layout
	};
}