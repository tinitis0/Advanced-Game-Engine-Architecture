/*! \file OpenGL_VertexArray.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "Platform/OpenGL/OpenGL_VertexArray.h"

namespace Engine
{
	namespace SDT
	{
		static GLenum toGL_Type(shaderDataType type)
		{
			switch (type)
			{
			case shaderDataType::Byte: return GL_UNSIGNED_BYTE; //!< Byte is GL_UNSIGNED_INT
			case shaderDataType::Byte2: return GL_UNSIGNED_BYTE; //!< Byte2 is GL_UNSIGNED_INT
			case shaderDataType::Byte3: return GL_UNSIGNED_BYTE; //!< Byte3 is GL_UNSIGNED_INT
			case shaderDataType::Byte4: return GL_UNSIGNED_BYTE; //!< Byte4 is GL_UNSIGNED_INT
			case shaderDataType::Short: return GL_SHORT;  //!< Short is GL_SHORT
			case shaderDataType::Short2: return GL_SHORT; //!< Short2 is GL_SHORT
			case shaderDataType::Short3: return GL_SHORT; //!< Short3 is GL_SHORT
			case shaderDataType::Short4: return GL_SHORT; //!< Short4 is GL_SHORT
			case shaderDataType::Float: return GL_FLOAT;  //!< Float is GL_FLOAT
			case shaderDataType::Float2: return GL_FLOAT; //!< Float2 is GL_FLOAT
			case shaderDataType::Float3: return GL_FLOAT; //!< Float3 is GL_FLOAT
			case shaderDataType::Float4: return GL_FLOAT; //!< Float4 is GL_FLOAT
			case shaderDataType::Int: return GL_INT; //!< Integer is GL_INT
			default: return GL_INVALID_ENUM; //!< Default return is an invalid enum
			}
		}
	}
	OpenGL_VertexArray::OpenGL_VertexArray()
	{
		glCreateVertexArrays(1, &m_OpenGL_ID); //!< Create Vertex Array based off OpenGL ID
		glBindVertexArray(m_OpenGL_ID); //!< Bind vertex array based off OpenGL ID
	}

	OpenGL_VertexArray::~OpenGL_VertexArray()
	{
		glDeleteVertexArrays(1, &m_OpenGL_ID); //!< Delete Vertex array
	}

	void OpenGL_VertexArray::addVertexBuffer(const std::shared_ptr<vertexBuffer>& vertexBuffer)
	{
		m_vertexBuffers.push_back(vertexBuffer); //!< Push Back Vertex Buffer

		glBindVertexArray(m_OpenGL_ID); //!< Binding vertex array based on OpenGL ID
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getRenderID()); //!< Bind array buffer on vertex buffer render ID

		const auto& layout = vertexBuffer->getLayout(); //!< Getting vertex buffer layout
		for (const auto& element : layout) //!< Each element of the layout
		{
			uint32_t normalised = GL_FALSE;
			if (element.m_normalised) { normalised = GL_TRUE; }
			glEnableVertexAttribArray(m_vertexAttribIndex); //!< Enable the Vertex Attribute array based off index
			glVertexAttribPointer(
				m_vertexAttribIndex,
				SDT::componentCount(element.m_dataType), // Data Type
				SDT::toGL_Type(element.m_dataType), // Float
				normalised, // normalised = true
				layout.getStride(), // Get layout
				(void*) element.m_offSet); // Position
			m_vertexAttribIndex++; // Increase vertex attribute index
		}
	}

	void OpenGL_VertexArray::setIndexBuffer(const std::shared_ptr<indexBuffer>& indexBuffer)
	{
		m_indexBuffer = indexBuffer; //!< Index buffer
	}
}