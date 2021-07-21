/*! \file RendererCommon.h */
#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include "Rendering/shaderDataType.h"
#include "Rendering/UniformBuffer.h"
#include "Rendering/vertexArray.h"
#include "Rendering/Textures.h"
#include "Rendering/Shader.h"
#include "renderCommands.h"
#include "independent/Rendering/SubTexture.h"
#include <memory>

namespace Engine
{
	using SceneWideUniforms = std::unordered_map < const char *, std::shared_ptr<UniformBuffer>>; //!< Uniform Buffers
	using SceneWideUniformsCorrect = std::unordered_map < const char *, void*>; //!< Uniform Buffers

	
	/* class RendererCommon */
	class RendererCommon
	{
	public:
		static void actionCommand(renderCommands * command)
		{
			command->action();
			//delete command;
		}

		static renderCommands * clearCommand;
		static renderCommands * clearColourAndDepth;;
		static renderCommands * setDepthTestEnabled;
		static renderCommands * setDepthTestDisable;
		static renderCommands * clearDepthBuffer;
		static renderCommands * setBlendEnabled;
		static renderCommands * setBlendDisabled;
		static renderCommands * setAlphaBlenFunc;
		static renderCommands * setWireFrame;
	};

	class Normal
	{
	public:
		static std::array<int16_t, 3> normalise(const glm::vec3& normal);

		static std::array<int16_t, 2> normalise(const glm::vec2& UV);

		static uint32_t pack(const glm::vec4& colour);

		static uint32_t pack(const glm::vec3& colour);
	};
}