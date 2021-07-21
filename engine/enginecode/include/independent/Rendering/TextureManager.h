/*! \file TextureManager.h */
#pragma once

#include <vector>

namespace Engine
{
	/*! \class Texture Mnager */
	class TextureManager
	{
	public:
		TextureManager(uint32_t capacity) : m_capacity(capacity), m_buffer(capacity, 0xFFFFFFFF) {} //!< Constructor that takes a capacity value
		inline bool full() { return m_full; } //!< Is buffer full?
		void clear(); //!< Clear Buffer
		bool getUnit(uint32_t texID, uint32_t& texUnit); //!< Returns whether the texture needs binding to unit
	private:
		uint32_t m_capacity; //!< Ring Buffer Capacity
		std::vector<uint32_t> m_buffer; //!< Buffer
		bool m_full = false; //!< Whether buffer is full (Set to false)
		uint32_t m_head = 0; //!< Head of buffer
		uint32_t m_tail = 0; //!< Tail of buffer
	};
}