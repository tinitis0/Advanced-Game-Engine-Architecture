/*! \file OpenGL_Shader.cpp */

#include "engine_pch.h"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Platform/OpenGL/OpenGL_Shader.h"
#include <fstream>
#include "systems/Logger.h"
#include <string>
#include <array>

namespace Engine
{
	OpenGL_Shader::OpenGL_Shader(const char * vertexFilePath, const char * fragmentFilePath)
	{
		std::string line, vertexSource, fragmentSource; //!< Read line by line
		// Vertex Shader
		std::fstream handle(vertexFilePath, std::ios::in); //!< Handle with in mode
		if (handle.is_open()) //!< If Handle is open...
		{
			while (getline(handle, line)) { vertexSource += (line + "\n"); } //!< Adding line to source
		}
		else
		{
			Logger::error("Could not open vertex shader source {0}", vertexFilePath); //!< Log error
			return; 
		}
		handle.close();
		// Fragment Shader
		handle.open(fragmentFilePath, std::ios::in); //!< Handle with in mode
		if (handle.is_open()) //!< If Handle is open...
		{
			while (getline(handle, line)) { fragmentSource += (line + "\n"); } //!< Adding line to source
		}
		else
		{
			Logger::error("Could not open fragment shader source {0}", fragmentFilePath); //!< Log error
			return;
		}
		handle.close();

		compileAndLink(vertexSource.c_str(), fragmentSource.c_str()); //!< Link and compile the two shaders
	}

	OpenGL_Shader::OpenGL_Shader(const char * filepath)
	{
		enum Region { None = -1, Vertex = 0, Fragment, Geometry, TessellationControl, TessellationEvaluation, Compute };
		std::string line; 
		std::array<std::string, Region::Compute + 1> source; //!< Strings Line & Source (In array)
		uint32_t region = Region::None; //!< Region in shader program e.g. Vertex

		std::fstream handle(filepath, std::ios::in); //!< Handle with in mode
		if (handle.is_open()) //!< If Handle is open...
		{
			while (getline(handle, line)) 
			{
				if (line.find("#region Vertex") != std::string::npos) { region = Region::Vertex; continue; } //!< Find where in region we are (Vertex)
				if (line.find("#region Fragment") != std::string::npos) { region = Region::Fragment; continue; } //!< Find where in region we are (Fragment)
				if (line.find("#region Geometry") != std::string::npos) { region = Region::Geometry; continue; } //!< Find where in region we are (Geometry)
				if (line.find("#region TessellationControl") != std::string::npos) { region = Region::TessellationControl; continue; } //!< Find where in region we are (TessellationControl)
				if (line.find("#region TessellationEvaluation") != std::string::npos) { region = Region::TessellationEvaluation; continue; } //!< Find where in region we are (TessellationEvaluationx)
				if (line.find("#region Compute") != std::string::npos) { region = Region::Compute; continue; } //!< Find where in region we are (Compute)
				
				if(region != Region::None) source[region] += (line + "\n"); //!< Adding line to source
			} 
		}
		else
		{
			Logger::error("Could not open shader source {0}", filepath); //!< Log error
			return;
		}
		handle.close();

		compileAndLink(source[Region::Vertex].c_str(), source[Region::Fragment].c_str()); //!< Link and compile the two shaders
	}

	OpenGL_Shader::~OpenGL_Shader()
	{
		glDeleteProgram(m_OpenGL_ID); //!< Delete Shader program
	}

	void OpenGL_Shader::uploadInt(const char * name, int value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name); //!< Upload int value
		glUniform1i(location, value);
	}

	void OpenGL_Shader::uploadFloat(const char * name, float value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name); //!< Upload float value
		glUniform1f(location, value);
	}

	void OpenGL_Shader::uploadFloat2(const char * name, glm::vec2 & value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name); //!< Upload float 2 value
		glUniform2f(location, value.x, value.y);
	}

	void OpenGL_Shader::uploadFloat3(const char * name, glm::vec3 & value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name); //!< Upload float 3 value
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGL_Shader::uploadFloat4(const char * name, const glm::vec4 & value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name); //!< Upload float 4 value
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGL_Shader::uploadMat4(const char * name, const glm::mat4 & value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name); //!< Upload int value
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGL_Shader::compileAndLink(const char * vertexShaderSrc, const char * fragmentShaderSrc)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //!< Create Vertex Shader

		const GLchar* source = vertexShaderSrc; //!< Get the source
		glShaderSource(vertexShader, 1, &source, 0); //!< Tells shader source
		glCompileShader(vertexShader); //!< Compile it

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled); //!< Check if compiled
		if (isCompiled == GL_FALSE) //!< Not compiled
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]); //!< Gets shader info
			Logger::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end())); //!< Log error message

			glDeleteShader(vertexShader); //!< Delete shader
			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //!< Create fragment shader

		source = fragmentShaderSrc; //!< Get source
		glShaderSource(fragmentShader, 1, &source, 0); //!< Tells shader source
		glCompileShader(fragmentShader); //!< Compile it

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled); //!< Check if compiled
		if (isCompiled == GL_FALSE) //!< If not compiled...
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]); //!< Gets shader info
			Logger::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end())); //!< Logs error message

			glDeleteShader(fragmentShader); //!< Delete Fragment Shader
			glDeleteShader(vertexShader); //!< Delete Vertex Shader

			return;
		}

		m_OpenGL_ID = glCreateProgram(); //!< Creates final shader program
		glAttachShader(m_OpenGL_ID, vertexShader); //!< Attach Vertex Shader
		glAttachShader(m_OpenGL_ID, fragmentShader); //!< Attach Fragment Shader
		glLinkProgram(m_OpenGL_ID); //!< Linked all together

		GLint isLinked = 0;
		glGetProgramiv(m_OpenGL_ID, GL_LINK_STATUS, (int*)&isLinked); //!< Check whether it has all linked
		if (isLinked == GL_FALSE) //!< If not linked...
		{
			GLint maxLength = 0;
			glGetProgramiv(m_OpenGL_ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_OpenGL_ID, maxLength, &maxLength, &infoLog[0]); //!< Get error
			Logger::error("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end())); //!< Log the error message

			glDeleteProgram(m_OpenGL_ID); //!< Delete the program
			glDeleteShader(vertexShader); //!< Delete the Vertex Shader
			glDeleteShader(fragmentShader); //!< Delete the Fragment Shader

			return;
		}

		glDetachShader(m_OpenGL_ID, vertexShader); //!< Detach Vertex Shader
		glDetachShader(m_OpenGL_ID, fragmentShader); //!< Detach Fragment Shader
	}
}