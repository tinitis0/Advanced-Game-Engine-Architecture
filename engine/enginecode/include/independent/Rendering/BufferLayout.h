/*! \file BufferLayout.h */
#pragma once
#include "shaderDataType.h"
#include <vector>

namespace Engine
{
	/*! \class VertexBufferElement
	* Class thats holding data on a single element in vertex buffer layout
	*/
	class VertexBufferElement
	{
	public:
		shaderDataType m_dataType; //!< Data type of element
		uint32_t m_size; //!< Size of the element
		uint32_t m_offSet; //!< Offset of element
		bool m_normalised; //!< Is it normalised?

		VertexBufferElement() {}; //!< Default Constructor
		VertexBufferElement(shaderDataType dataType, bool normalised = false) : //!< Takes dataType and a bool
			m_dataType(dataType), //!< m_dataType takes a dataType 
			m_size(SDT::size(dataType)), //!< m_size takes a dataType 
			m_offSet(0), //!< m_offSet defaulted to 0 
			m_normalised(normalised) //!< m_normalised takes the normalised bool
		{} //!< Constrcutor with parameters
	};

/*! \class UniformBufferElement
* Class thats holding data on a single element in uniform buffer layout
*/
	class UniformBufferElement
	{
	public:
		const char * m_name; //!< Name
		shaderDataType m_dataType; //!< Data type of element
		uint32_t m_size; //!< Size of the element
		uint32_t m_offSet; //!< Offset of element

		UniformBufferElement() {}; //!< Default Constructor
		UniformBufferElement(const char * name, shaderDataType dataType) : //!< Takes dataType and a bool
			m_name(name),
			m_dataType(dataType), //!< m_dataType takes a dataType 
			m_size(SDT::std140Alignment(dataType)), //!< m_size takes a dataType 
			m_offSet(0) //!< m_offSet defaulted to 0 
		{} //!< Constrcutor with parameters
	};


	/*! \class BufferLayout 
	* Abstraction of a buffer layout
	*/
	template <class G>
	class BufferLayout
	{
	public:
		BufferLayout<G>() {}; //!< Default Constructor
		BufferLayout<G>(const std::initializer_list<G>& element, uint32_t stride = 0) : m_element(element), m_stride(stride) { calcStrideAndOffset(); } //!< Constrctor with data
		inline uint32_t getStride() const { return m_stride; } //!< Get stride function
		void addElement(G element);
		inline typename std::vector<G>::iterator begin() {return m_element.begin();}//!< Begin Iterator
		inline typename std::vector<G>::iterator end() { return m_element.end(); }//!< End Iterator
		inline typename std::vector<G>::const_iterator begin() const { return m_element.begin(); }//!< Begin Iterator
		inline typename std::vector<G>::const_iterator end() const { return m_element.end(); }//!< End Iterator

	private:
		std::vector<G> m_element; //!< Buffer Element
		uint32_t m_stride; //!< Width in bytes of buffer line
		void calcStrideAndOffset(); //!< Calculate stride and offset based on element
	};

	template <class G>
	void BufferLayout<G>::addElement(G element) //!< Add new element
	{
		m_element.push_back(element);
		calcStrideAndOffset();
	}

	template <class G>
	void BufferLayout<G>::calcStrideAndOffset() //!< Calculate the offsets & stride
	{
		uint32_t l_offset = 0;

		for (auto& element : m_element) //!< Range based loop
		{
			element.m_offSet = l_offset; //!< m_offset equal to local offset
			l_offset += element.m_size; //!< Calculate offset
		}

		if (m_stride == 0) m_stride = l_offset; //!< Stride is the local offset
	}

	using VertexBufferLayout = BufferLayout<VertexBufferElement>; //!< When using vertexBufferLayout, it means BufferLayout with a vertex buffer element
	using UniformBufferLayout = BufferLayout<UniformBufferElement>; //!< When using vertexBufferLayout, it means BufferLayout with a uniform buffer element
}
