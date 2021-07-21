/*! \file Shader.h */
#pragma once
#include <cstdint>
#include "glm/glm.hpp"

namespace Engine
{
	/*! \class Shader */
	class Shader
	{
	public:
		virtual ~Shader() {}; //!< Destructor
		virtual inline uint32_t getRenderID() const = 0; //!< Get the OpenGL ID

		virtual void uploadInt(const char* name, int value) = 0; //!< Upload a sample 2D
		virtual void uploadFloat(const char* name, float value) = 0; //!< Upload float combinations
		virtual void uploadFloat2(const char* name, glm::vec2& value) = 0; //!< Upload float combinations
		virtual void uploadFloat3(const char* name, glm::vec3& value) = 0; //!< Upload float combinations
		virtual void uploadFloat4(const char* name, const glm::vec4& value) = 0; //!< Upload float combinations
		virtual void uploadMat4(const char* name, const glm::mat4& value) = 0; //!< Upload Matrices

		static Shader* create(const char* vertexFilePath, const char* fragmentFilePath); //!< Create using vertex & fragment file path
		static Shader* create(const char* filepath); //!< Create using a filepath
	};
}
