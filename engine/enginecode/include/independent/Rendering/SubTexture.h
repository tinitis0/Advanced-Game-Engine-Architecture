/*! \file SubTexture.h */
#pragma once

#include "Platform/OpenGL/OpenGL_Textures.h"
#include <memory>
#include <glm/glm.hpp>

namespace Engine
{
	/*! \class SubTexture */
	class SubTexture
	{
	private:
		std::shared_ptr<Textures> m_texture; //!< Holds the texture
		glm::vec2 m_UVStart; //!< Holds UV Start
		glm::vec2 m_UVEnd; //!< Holds UV End
		glm::ivec2 m_size;//!< Storing Size in pixels

	public:
		SubTexture() {}; //!< Default Constructor
		SubTexture(const std::shared_ptr<Textures>& texture, const glm::vec2& UVStart, const glm::vec2& UVEnd); //!< Constructor that takes texture & UV params
		inline glm::vec2 getUVStart() { return m_UVStart; } //!< Getter for UV Start
		inline glm::vec2 getUVEnd() { return m_UVEnd; } //!< Getter for UV End
		glm::vec2 getSize() { return m_size; } //!< Getter for size
		glm::vec2 getSizef() { return { static_cast<float>(m_size.x), static_cast<float>(m_size.y) }; } //!< Store as float
	
		inline uint32_t getWidth() { return m_size.x; } //!< Getter for width data
		inline uint32_t getHeight() { return m_size.y; } //!< Getter for height data
		inline uint32_t getWidthf() { return static_cast<float> (m_size.x); } //!< Getter for width data as float
		inline uint32_t getHeightf() { return static_cast<float> (m_size.y); } //!< Getter for height data as float
		// Methods
		float transformU(float U); //!< Transform original to atlas co ordinates
		float transformV(float V); //!< Transform original to atlas co ordinates
		glm::vec2 transformUV(glm::vec2 UV); //!< Transforming the UV

		std::shared_ptr<Textures> getTexture() { return m_texture; }
	};
}