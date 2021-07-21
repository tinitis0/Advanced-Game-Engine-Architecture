/*! \file 2D_Renderer.h */
#pragma once

#include "RendererCommon.h"
#include "ft2build.h"
#include "freetype/freetype.h"

namespace Engine
{
	struct ApplicationProps;

	/*! \class Quad */

	class Quad
	{
	public:
		Quad() {} //!< Quad
		static Quad createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents); //!< Half Extents
		static Quad createCentreHalfExtents(const glm::vec2& centre, float halfExtents); //!< Half Extents
		static Quad createTopLeftSize(const glm::vec2& topLeft, const glm::vec2& size); //!< Half Extents
		static Quad createTopLeftSize(const glm::vec2& topLeft, float size); //!< Half Extents
		static Quad createTopLeftBottomRight(const glm::vec2& topLeft, const glm::vec2& bottomRight); //!< Half Extents
		
		void setTranslate(glm::vec3 translate) { m_translate = translate; }
	
	private:
		glm::vec3 m_translate = glm::vec3(0.f); //!< Translation Vector
		glm::vec3 m_scale = glm::vec3(1.f); //!< Scale vector
		friend class Renderer2D;
	};

	/*!  \class Renderer2D 
	*   \brief Class which allows the rendering of simple 2D 
	*/

	class Renderer2D
	{
	public:
		static void init(ApplicationProps params); //!< Initialise internal data
		
		static void begin(const SceneWideUniformsCorrect& swu); //!< Begin Scene
		static void submit(const Quad& quad, const glm::vec4& tint); //!< Render Quad with a tint
		static void submit(const Quad& quad, const std::shared_ptr<Textures>& texture); //!< Render Quad with a texture
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Textures>& texture); //!< Render Quad with a tint & texture
		static void submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees = false); //!< Render Quad with a tint at an angle
		static void submit(const Quad& quad, const std::shared_ptr<Textures>& texture, float angle, bool degrees = false); //!< Render Quad with a texture at an angle
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Textures>& texture, float angle, bool degrees = false); //!< Render Quad with a tint & texture at an angle
		

		static void submit(char cha, const glm::vec2& position, float& advance, const glm::vec4& tint); //!< Render single character with a tint
		static void submit(const char * string, const glm::vec2& position, const glm::vec4& tint); //!< Render a string with a tint

		static void end(); //!< End Scene

		//static void getTextSize(const char * text);
	private:
		struct InternalData //!< Internal Data (Texture, Tint, Shader)
		{
			std::shared_ptr<Textures> defaultTexture; //!< Default Texture
			glm::vec4 defaultTint; //!< Default Tint
			std::shared_ptr<Shader> shader; //!< Shader Used
			std::shared_ptr<vertexArray> VAO; //!< Vertex Array
			glm::mat4 model; //!< Model Used
			std::shared_ptr<UniformBuffer> UBO;

			FT_Library ft; //!< Freetype System
			FT_Face fontFace; //!< Font Face
			std::shared_ptr<Textures> fontTexture; //!< Texture
			glm::ivec2 glyphBufferDims; //!< Glyph buffer Dims
			uint32_t glyphBufferSize; //!< Amount of memory in buffer
			std::shared_ptr<unsigned char> glyphBuffer; //!< Glyph Buffer
		};

		static std::shared_ptr<InternalData> s_data; //!< Internal Data

		static void RtoRGBA(unsigned char * Rbuffer, uint32_t width, uint32_t height); // RtoRGBA Converts from 1 channel to 4 channels

	};
}