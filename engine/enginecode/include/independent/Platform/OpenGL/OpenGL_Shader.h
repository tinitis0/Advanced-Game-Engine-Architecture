/*! \file OpenGL_Shader.h */
#pragma once
#include <cstdint>
#include "glm/glm.hpp"
#include "Rendering/Shader.h"

namespace Engine
{
	/*! \class OpenGL_Shader */
	class OpenGL_Shader : public Shader
	{
	public:
		OpenGL_Shader(const char* vertexFilePath, const char* fragmentFilePath); //!< Constructor that takes vertex and fragment shader file paths
		OpenGL_Shader(const char* filepath); //!< Takes file path
		virtual ~OpenGL_Shader(); //!< Destructor
		virtual inline uint32_t getRenderID() const override { return m_OpenGL_ID; } //!< Get the OpenGL ID

		void uploadInt(const char* name, int value); //!< Upload a sample 2D
		void uploadFloat(const char* name, float value); //!< Upload float combinations
		void uploadFloat2(const char* name, glm::vec2& value); //!< Upload float combinations
		void uploadFloat3(const char* name, glm::vec3& value); //!< Upload float combinations
		void uploadFloat4(const char* name, const glm::vec4& value); //!< Upload float combinations
		void uploadMat4(const char* name, const glm::mat4& value); //!< Upload Matrices
	private:
		uint32_t m_OpenGL_ID; //!< OpenGL ID
		void compileAndLink(const char* vertexShaderSrc, const char* fragmentShaderSrc); //!< Takes fragment and vertex shader source due to 2 constructors
	};
}