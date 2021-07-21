/*! \file SubTexture.cpp */

#include "engine_pch.h"
#include "Rendering/SubTexture.h"

namespace Engine
{
	SubTexture::SubTexture(const std::shared_ptr<Textures>& texture, const glm::vec2 & UVStart, const glm::vec2 & UVEnd) : 
		m_texture(texture),
		m_UVStart(UVStart),
		m_UVEnd(UVEnd)

	{
		m_size.x = static_cast<int>(m_UVEnd.x - m_UVStart.x) * m_texture->getWidthf(); //!< Working out size on X axis (UV end - start, multiplied by width as floating point number)
		m_size.x = static_cast<int>(m_UVEnd.y - m_UVStart.y) * m_texture->getHeightf(); //!< Working out size on Y axis (UV end - start, multiplied by height as floating point number)
	}

	float SubTexture::transformU(float U)
	{
		return m_UVStart.x + ((m_UVEnd.x - m_UVStart.x) * U); //!< Transform on X
	}

	float SubTexture::transformV(float V)
	{
		return m_UVStart.y + ((m_UVEnd.y - m_UVStart.y) * V); //!< Transform on Y
	}

	glm::vec2 SubTexture::transformUV(glm::vec2 UV)
	{
		return m_UVStart + ((m_UVEnd - m_UVStart) * UV); //!< Transform the UV
	}
}