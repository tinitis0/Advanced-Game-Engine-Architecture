/*! \file renderCommands.cpp */

#include "engine_pch.h"
#include "Platform/Renderer/renderCommands.h"
#include "Platform/OpenGL/OpenGL_RenderCommands.h"
#include "Rendering/RenderAPI.h"
#include "systems/Logger.h"
#include <glad/glad.h>

namespace Engine
{
	
	renderCommands * RendererCommon::clearCommand = renderCommands::getSetClearColourCommand(0.52f, 0.8f, 0.92f, 1.0f); //!< Render Command to set colour
	renderCommands * RendererCommon::clearColourAndDepth = renderCommands::getClearColourAndDepthBufferCommand(); //!< Command to clear Colour & Depth Buffer
	renderCommands * RendererCommon::setDepthTestEnabled = renderCommands::getSetDepthTest(true); //!< Command to enable Depth Test
	renderCommands * RendererCommon::setDepthTestDisable = renderCommands::getSetDepthTest(false); //!< Command to disable Depth Test
	renderCommands * RendererCommon::clearDepthBuffer = renderCommands::getClearDepthBufferCommand(); //!< Command to clear Depth Buffer Alone
	renderCommands * RendererCommon::setBlendEnabled = renderCommands::getSetBlend(true); //!< Command to enable GL_BLEND
	renderCommands * RendererCommon::setBlendDisabled = renderCommands::getSetBlend(false); //!< Command to disable GL_BLEND
	renderCommands * RendererCommon::setAlphaBlenFunc = renderCommands::getSetAlphaBlendFunction(); //!< Command to set Alpha blend
	renderCommands * RendererCommon::setWireFrame = renderCommands::getSetWireFrame();


	renderCommands * renderCommands::getClearColourAndDepthBufferCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			Logger::error("Direct 3D not supported!"); //!< Log Error
			break;
		case RenderAPI::API::None:
			Logger::error("No API Active!"); //!< Log Error
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLGetClearColourAndDepthBufferCommand(); //!< Return OpenGL Command (Clear Colour & Depth Buffer)
			break;
		case RenderAPI::API::Vulkan:
			Logger::error("Vulkan not supported!"); //!< Log Error
			break;
		default:
			Logger::error("No API Active!"); //!< Log Error
		}
	}

	renderCommands * renderCommands::getClearDepthBufferCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			Logger::error("Direct 3D not supported!"); //!< Log Error
			break;
		case RenderAPI::API::None:
			Logger::error("No API Active!"); //!< Log Error
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLGetClearDepthBufferCommand(); //!< Return OpenGL Command (Clear Depth Buffer)
			break;
		case RenderAPI::API::Vulkan:
			Logger::error("Vulkan not supported!"); //!< Log Error
			break;
		default:
			Logger::error("No API Active!"); //!< Log Error
		}
	}

	renderCommands * renderCommands::getClearColourBufferCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			Logger::error("Direct 3D not supported!"); //!< Log Error
			break;
		case RenderAPI::API::None:
			Logger::error("No API Active!"); //!< Log Error
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLGetClearColourBufferCommand(); //!< Return OpenGL Command (Clear Colour Buffer)
			break;
		case RenderAPI::API::Vulkan:
			Logger::error("Vulkan not supported!"); //!< Log Error
			break;
		default:
			Logger::error("No API Active!"); //!< Log Error
		}
	}

	renderCommands * renderCommands::getSetClearColourCommand(float r, float g, float b, float a)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			Logger::error("Direct 3D not supported!"); //!< Log Error
			break;
		case RenderAPI::API::None:
			Logger::error("No API Active!"); //!< Log Error
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLSetClearColourCommand(r, g, b, a); //!< Return OpenGL Command (Set Clear Colour (RGBA Values))
			break;
		case RenderAPI::API::Vulkan:
			Logger::error("Vulkan not supported!"); //!< Log Error
			break;
		default:
			Logger::error("No API Active!"); //!< Log Error
		}
	}

	renderCommands * renderCommands::getSetDepthTest(bool enabled)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			Logger::error("Direct 3D not supported!"); //!< Log Error
			break;
		case RenderAPI::API::None:
			Logger::error("No API Active!"); //!< Log Error
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLGetSetDepthTest(enabled); //!< Return OpenGL Command (Set Depth Test (Boolean Value))
			break;
		case RenderAPI::API::Vulkan:
			Logger::error("Vulkan not supported!"); //!< Log Error
			break;
		default:
			Logger::error("No API Active!"); //!< Log Error
		}
	}

	renderCommands * renderCommands::getSetBlend(bool enabled)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			Logger::error("Direct 3D not supported!"); //!< Log Error
			break;
		case RenderAPI::API::None:
			Logger::error("No API Active!"); //!< Log Error
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLGetSetBlendCommand(enabled); //!< Return OpenGL Command (Set Depth Test (Boolean Value))
			break;
		case RenderAPI::API::Vulkan:
			Logger::error("Vulkan not supported!"); //!< Log Error
			break;
		default:
			Logger::error("No API Active!"); //!< Log Error
		}
	}

	renderCommands * renderCommands::getSetAlphaBlendFunction()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			Logger::error("Direct 3D not supported!"); //!< Log Error
			break;
		case RenderAPI::API::None:
			Logger::error("No API Active!"); //!< Log Error
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLGetSetAlphaBlendFunction(); //!< Return OpenGL Command (BlendFunction)
			break;
		case RenderAPI::API::Vulkan:
			Logger::error("Vulkan not supported!"); //!< Log Error
			break;
		default:
			Logger::error("No API Active!"); //!< Log Error
		}
	}

	renderCommands * renderCommands::getSetWireFrame()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			Logger::error("Direct 3D not supported!"); //!< Log Error
			break;
		case RenderAPI::API::None:
			Logger::error("No API Active!"); //!< Log Error
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLGetSetWireFrame(); //!< Return OpenGL Command (Clear Colour & Depth Buffer)
			break;
		case RenderAPI::API::Vulkan:
			Logger::error("Vulkan not supported!"); //!< Log Error
			break;
		default:
			Logger::error("No API Active!"); //!< Log Error
		}
	}
}