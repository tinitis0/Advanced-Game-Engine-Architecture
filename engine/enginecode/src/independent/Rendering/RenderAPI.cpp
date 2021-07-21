/*! \file RenderAPI.cpp */

#include "engine_pch.h"
#include "systems/Logger.h"

#include "Rendering/RenderAPI.h"
#include "Rendering/indexBuffer.h"
#include "Rendering/vertexBuffer.h"
#include "Rendering/vertexArray.h"
#include "Rendering/Shader.h"
#include "Rendering/Textures.h"
#include "Rendering/UniformBuffer.h"

#include "Platform/OpenGL/OpenGL_IndexBuffer.h"
#include "Platform/OpenGL/OpenGL_VertexBuffer.h"
#include "Platform/OpenGL/OpenGL_VertexArray.h"
#include "Platform/OpenGL/OpenGL_Shader.h"
#include "Platform/OpenGL/OpenGL_Textures.h"
#include "Platform/OpenGL/OpenGL_UniformBuffer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"
#include "Platform/OpenGL/OpenGL_RenderBuffer.h"

namespace Engine
{
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL; //!< Rendering API used is OpenGL

	indexBuffer* indexBuffer::create(uint32_t * indices, uint32_t count)
	{
		switch (RenderAPI::getAPI()) //!< Switch API
		{
		case RenderAPI::API::None: //!< No Rendering API Active
			Logger::error("No Rendering API Active");
			break;

		case RenderAPI::API::OpenGL: //!< OpenGL API Active
			return new OpenGL_IndexBuffer(indices, count); //!< Creating new OpenGL index buffer that takes the count and indices
			break;

		case RenderAPI::API::Direct3D: //!< Direct3D API Active (Not Supported)
			Logger::error("Direct3D Not Supported"); //!< Log not supported
			break;

		case RenderAPI::API::Vulkan: //!< Vulkan API Active (Not Supported)
			Logger::error("Vulkan Not Supported"); //!< Log not supported
			break;
		}

		return nullptr; //!< If none of above happen
	}

	vertexBuffer* vertexBuffer::create(void* vertices, uint32_t size, const VertexBufferLayout& layout)
	{
		switch (RenderAPI::getAPI()) //!< Switch API
		{
		case RenderAPI::API::None: //!< No Rendering API Active
			Logger::error("No Rendering API Active");
			break;

		case RenderAPI::API::OpenGL: //!< OpenGL API Active
			return new OpenGL_VertexBuffer(vertices, size, layout);
			break;

		case RenderAPI::API::Direct3D: //!< Direct3D API Active (Not Supported)
			Logger::error("Direct3D Not Supported"); //!< Log not supported
			break;

		case RenderAPI::API::Vulkan: //!< Vulkan API Active (Not Supported)
			Logger::error("Vulkan Not Supported"); //!< Log not supported
			break;
		}
	}

	vertexArray* vertexArray::create()
	{
		switch (RenderAPI::getAPI()) //!< Switch API
		{
		case RenderAPI::API::None: //!< No Rendering API Active
			Logger::error("No Rendering API Active");
			break;

		case RenderAPI::API::OpenGL: //!< OpenGL API Active
			return new OpenGL_VertexArray;
			break;

		case RenderAPI::API::Direct3D: //!< Direct3D API Active (Not Supported)
			Logger::error("Direct3D Not Supported"); //!< Log not supported
			break;

		case RenderAPI::API::Vulkan: //!< Vulkan API Active (Not Supported)
			Logger::error("Vulkan Not Supported"); //!< Log not supported
			break;
		}
	}

	Shader* Shader::create(const char* vertexFilePath, const char* fragmentFilePath)
	{
		switch (RenderAPI::getAPI()) //!< Switch API
		{
		case RenderAPI::API::None: //!< No Rendering API Active
			Logger::error("No Rendering API Active");
			break;

		case RenderAPI::API::OpenGL: //!< OpenGL API Active
			return new OpenGL_Shader(vertexFilePath, fragmentFilePath);
			break;

		case RenderAPI::API::Direct3D: //!< Direct3D API Active (Not Supported)
			Logger::error("Direct3D Not Supported"); //!< Log not supported
			break;

		case RenderAPI::API::Vulkan: //!< Vulkan API Active (Not Supported)
			Logger::error("Vulkan Not Supported"); //!< Log not supported
			break;
		}
	}

	Shader* Shader::create(const char* filepath)
	{
		switch (RenderAPI::getAPI()) //!< Switch API
		{
		case RenderAPI::API::None: //!< No Rendering API Active
			Logger::error("No Rendering API Active");
			break;

		case RenderAPI::API::OpenGL: //!< OpenGL API Active
			return new OpenGL_Shader(filepath);
			break;

		case RenderAPI::API::Direct3D: //!< Direct3D API Active (Not Supported)
			Logger::error("Direct3D Not Supported"); //!< Log not supported
			break;

		case RenderAPI::API::Vulkan: //!< Vulkan API Active (Not Supported)
			Logger::error("Vulkan Not Supported"); //!< Log not supported
			break;
		}
	}

	Textures* Textures::create(const char* filepath)
	{
		switch (RenderAPI::getAPI()) //!< Switch API
		{
		case RenderAPI::API::None: //!< No Rendering API Active
			Logger::error("No Rendering API Active");
			break;

		case RenderAPI::API::OpenGL: //!< OpenGL API Active
			return new OpenGL_Textures(filepath);
			break;

		case RenderAPI::API::Direct3D: //!< Direct3D API Active (Not Supported)
			Logger::error("Direct3D Not Supported"); //!< Log not supported
			break;

		case RenderAPI::API::Vulkan: //!< Vulkan API Active (Not Supported)
			Logger::error("Vulkan Not Supported"); //!< Log not supported
			break;
		}
	}

	Textures* Textures::create(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data)
	{
		switch (RenderAPI::getAPI()) //!< Switch API
		{
		case RenderAPI::API::None: //!< No Rendering API Active
			Logger::error("No Rendering API Active");
			break;

		case RenderAPI::API::OpenGL: //!< OpenGL API Active
			return new OpenGL_Textures(width, height, channels, data);
			break;

		case RenderAPI::API::Direct3D: //!< Direct3D API Active (Not Supported)
			Logger::error("Direct3D Not Supported"); //!< Log not supported
			break;

		case RenderAPI::API::Vulkan: //!< Vulkan API Active (Not Supported)
			Logger::error("Vulkan Not Supported"); //!< Log not supported
			break;
		}
	}

	UniformBuffer* UniformBuffer::create(const UniformBufferLayout& layout)
	{
		switch (RenderAPI::getAPI()) //!< Switch API
		{
		case RenderAPI::API::None: //!< No Rendering API Active
			Logger::error("No Rendering API Active");
			break;

		case RenderAPI::API::OpenGL: //!< OpenGL API Active
			return new OpenGL_UniformBuffer(layout);
			break;

		case RenderAPI::API::Direct3D: //!< Direct3D API Active (Not Supported)
			Logger::error("Direct3D Not Supported"); //!< Log not supported
			break;

		case RenderAPI::API::Vulkan: //!< Vulkan API Active (Not Supported)
			Logger::error("Vulkan Not Supported"); //!< Log not supported
			break;
		}
	}

	FrameBuffer* FrameBuffer::create(const glm::ivec2& size, const FrameBufferLayout& layout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None: //!< No Rendering API Active
			Logger::error("No Rendering API Active");
			break;

		case RenderAPI::API::OpenGL: //!< OpenGL API Active
			return new OpenGLFrameBuffer(size, layout);
			break;

		case RenderAPI::API::Direct3D: //!< Direct3D API Active (Not Supported)
			Logger::error("Direct3D Not Supported"); //!< Log not supported
			break;

		case RenderAPI::API::Vulkan: //!< Vulkan API Active (Not Supported)
			Logger::error("Vulkan Not Supported"); //!< Log not supported
			break;
		}

		return nullptr;
	}


	FrameBuffer* FrameBuffer::createDefault()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None: //!< No Rendering API Active
			Logger::error("No Rendering API Active");
			break;

		case RenderAPI::API::OpenGL: //!< OpenGL API Active
			return new OpenGLFrameBuffer();
			break;

		case RenderAPI::API::Direct3D: //!< Direct3D API Active (Not Supported)
			Logger::error("Direct3D Not Supported"); //!< Log not supported
			break;

		case RenderAPI::API::Vulkan: //!< Vulkan API Active (Not Supported)
			Logger::error("Vulkan Not Supported"); //!< Log not supported
			break;
		}

		return nullptr;
	}

	RenderBuffer* RenderBuffer::create(AttachmentType& type, glm::ivec2& size)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None: //!< No Rendering API Active
			Logger::error("No Rendering API Active");
			break;

		case RenderAPI::API::OpenGL: //!< OpenGL API Active
			return new OpenGL_RenderBuffer(type, size);
			break;

		case RenderAPI::API::Direct3D: //!< Direct3D API Active (Not Supported)
			Logger::error("Direct3D Not Supported"); //!< Log not supported
			break;

		case RenderAPI::API::Vulkan: //!< Vulkan API Active (Not Supported)
			Logger::error("Vulkan Not Supported"); //!< Log not supported
			break;
		}

		return nullptr;
	}
}
