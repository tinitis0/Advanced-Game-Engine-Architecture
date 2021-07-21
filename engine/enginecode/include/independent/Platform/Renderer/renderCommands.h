/*! \file renderCommands.h */
#pragma once

#include <functional>
#include "independent/Rendering/RenderAPI.h"

namespace Engine
{
	/*! \class RendererCommon */
	class RendererCommon;

	/*! \class renderCommands 
	* All of the render commands
	*/
	class renderCommands
	{
	public:
		virtual void action() = 0;
		//enum class Commands { clearDepthBuffer, clearColourBuffer, clearColourAndDepthBuffer, setClearColour, setDepthTest }; //!< All Commands
	public:
		static renderCommands * getClearColourAndDepthBufferCommand(); //!< Get clear colour and depth buffer command
		static renderCommands * getClearDepthBufferCommand(); //!< Get clear depth buffer command
		static renderCommands * getClearColourBufferCommand(); //!< Get clear colour buffer command
		static renderCommands * getSetClearColourCommand(float r, float g, float b, float a); //!< Set clear colour colour command RGBA
		static renderCommands * getSetDepthTest(bool enabled); //!< Set depth test boolean 
		static renderCommands * getSetBlend(bool enabled); //!< Set blend boolean
		static renderCommands * getSetAlphaBlendFunction(); //!< Set alpha blend function
		static renderCommands * getSetWireFrame();

	};
}