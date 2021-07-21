/*! \file TextureManager.cpp */
#include "engine_pch.h"
#include "Rendering/TextureManager.h"

namespace Engine
{
	void TextureManager::clear()
	{
		m_head = 0; //!< Reset Head
		m_tail = 0; //!< Reset Tail
		m_full = false; //!< No longer full
		std::fill(m_buffer.begin(), m_buffer.end(), 0xFFFFFFFF); //!< Fills with maximum of 8bit
	}
	bool TextureManager::getUnit(uint32_t texID, uint32_t & texUnit)
	{
		// Check if texture is already binded
		for (int i = m_tail; i < m_head; i++)
		{
			if (m_buffer.at(i) == texID)
			{
				texUnit = i; //!< Texture Unit equal to i (tail)
				return false; //!< Do not need to bind
			}
		}

		// Texture unit not bound

		// Is space available in the buffer
		if (m_full) clear(); //!< Clear the buffer

		// Put texture ID in buffer
		m_buffer.at(m_head) = texID; //!< Head is texture ID
		texUnit = m_head; //!< Texture unity is now the head of buffer
		
		// Checks if capacity is full
		m_head = (++m_head) % m_capacity;
		if (m_head == m_tail) m_full = true; //!< If the head is the same as the tail the buffer is full
		
		return true;
	}
}