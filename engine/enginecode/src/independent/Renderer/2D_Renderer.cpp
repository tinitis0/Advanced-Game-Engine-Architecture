/*! \file 2D_Renderer.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Platform/Renderer/2D_Renderer.h"
#include "systems/Logger.h"
#include "core/application.h"

namespace Engine
{

	std::shared_ptr<Renderer2D::InternalData> Renderer2D::s_data = nullptr; //!< Data is a null pointer

	void Renderer2D::init(ApplicationProps params)
	{
		s_data.reset(new InternalData); //!< Creates new internal data

		unsigned char whitePx[4] = { 255,255,255,255 }; //!< White pixel
		s_data->defaultTexture.reset(Textures::create(1, 1, 4, whitePx)); //!< Width of 1, Height of 1 and 4 Channels. Default Texture

		s_data->defaultTint = { 1.f, 1.f, 1.f, 1.f }; //!< Deafult tint is white

		s_data->model = glm::mat4(1.0f); //!< Identity Matrix

		s_data->shader.reset(Shader::create("./assets/shaders/quad1.glsl")); //!< Shader Data

		UniformBufferLayout camLayout = { { "u_projection", shaderDataType::Mat4 }, { "u_view", shaderDataType::Mat4 } };
		s_data->UBO.reset(UniformBuffer::create(camLayout));
		s_data->UBO->attachShaderBlock(s_data->shader, "b_camera");

		float vertices[4 * 4] =
		{
			-0.5f, -0.5f, 0.f, 0.f, // Top Left
			-0.5f,	0.5f, 0.f, 1.f, // Bottom Left
			 0.5f,	0.5f, 1.f, 1.f, // Bottom Right
			 0.5f, -0.5f, 1.f, 0.f, // Top Right
		};

		uint32_t indices[4] = { 0,1,2,3 }; //!< 4 Indices

		std::shared_ptr<vertexBuffer> VBO; //!< Vertex Buffer Object
		std::shared_ptr<indexBuffer> IBO; //!< Index Buffer Object

		s_data->VAO.reset(vertexArray::create()); //!< Create vertexArray
		VBO.reset(vertexBuffer::create(vertices, sizeof(vertices), VertexBufferLayout({ shaderDataType::Float2, shaderDataType::Float2 }))); //!< Create vertex buffer with 4 * 4 vertices
		IBO.reset(indexBuffer::create(indices, 4)); //!< Creating an index buffer with 4 indices
		s_data->VAO->addVertexBuffer(VBO); //!< Adding Vertex Buffer
		s_data->VAO->setIndexBuffer(IBO); //!< Adding Index Buffer

		// Filepath to the font
		const char * filePath = "./assets/Fonts/BadaBoom BB.TTF"; //!< Font Filepath

		// Dim of the glyph buffer
		s_data->glyphBufferDims = { 256, 256 };
		s_data->glyphBufferSize = s_data->glyphBufferDims.x * s_data->glyphBufferDims.y * 4 * sizeof(unsigned char); //!< Buffer size (Buffer dim X * Y * Channels(4) * Unsigned Char(1))
		s_data->glyphBuffer.reset(static_cast<unsigned char *>(malloc(s_data->glyphBufferSize))); //!< Assigning buffer size

		// Initialise Library
		if (FT_Init_FreeType(&s_data->ft)) { Logger::error("Error Freetype could not be initialised!"); } //!< Initialise freetype library in internal data & logging an error if cannot be initialised
		
		// Load A Font
		if (FT_New_Face(s_data->ft, filePath, 0, &s_data->fontFace)) { Logger::error("Could not load font: {0}", filePath); } //!< Loading font filepath & logging an error if font is not found

		// Set the character size for font
		int32_t fontSize = 40;
		if (FT_Set_Pixel_Sizes(s_data->fontFace, 0, fontSize)) { Logger::error("Cannot set the font size {0}", fontSize); } //!< Setting font size, and logging an error if cannot display size
	
		// Init Font Text
		s_data->fontTexture.reset(Textures::create(s_data->glyphBufferDims.x, s_data->glyphBufferDims.y, 4, nullptr)); //!< Create texture with width & height 256 and 4 channels
		
		// Fill glyph buffer
		memset(s_data->glyphBuffer.get(), 255, s_data->glyphBufferSize); //!< Destination = glyphBuffer, 255 = White, Size = glyphBufferSize
		
		// Send glyph buffer to the texture
		s_data->fontTexture->edit(0, 0, s_data->glyphBufferDims.x, s_data->glyphBufferDims.y, s_data->glyphBuffer.get()); //!< Edit texture (Offset.x, Offset.y, Height, Width, Data)
	}

	void Renderer2D::begin(const SceneWideUniformsCorrect & swu)
	{
		// Bind Shader
		glUseProgram(s_data->shader->getRenderID());

		for (auto& dataPair : swu)
		{
			s_data->UBO->uploadData(dataPair.first, dataPair.second);
		}

		// Bind the geometry
		glBindVertexArray(s_data->VAO->getRenderID()); //!< Bind Vertex Array
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer()->getRenderID()); //!< Binding Buffer
	}

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint)
	{
		Renderer2D::submit(quad, tint, s_data->defaultTexture); //!< Submit without texture but with quad and tint
	}

	void Renderer2D::submit(const Quad & quad, const std::shared_ptr<Textures>& texture)
	{
		Renderer2D::submit(quad, s_data->defaultTint, texture); //!< Submit without a tint, however a texture
	}

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint, const std::shared_ptr<Textures>& texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture->getRenderID()); //!< Set default white texture
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale); //!< Translate then scale

		s_data->shader->uploadInt("u_texData", 0); //!< Upload texture data
		s_data->shader->uploadFloat4("u_tint", tint); //!< Upload Tint
		s_data->shader->uploadMat4("u_model", s_data->model); //!< Upload model matrix


		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr); //!< Draw quads
	}

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint, float angle, bool degrees)
	{
		Renderer2D::submit(quad, tint, s_data->defaultTexture, angle, degrees); //!< Submit without texture but with quad and tint and an angle and degrees
	}

	void Renderer2D::submit(const Quad & quad, const std::shared_ptr<Textures>& texture, float angle, bool degrees)
	{
		Renderer2D::submit(quad, s_data->defaultTint, texture, angle, degrees); //!< Submit without a tint, however a texture and angle and degrees
	}

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint, const std::shared_ptr<Textures>& texture, float angle, bool degrees)
	{
		if (degrees) angle = glm::radians(angle); //!< Convert to radians
	
		glBindTexture(GL_TEXTURE_2D, texture->getRenderID()); //!< Set default white texture
		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.f), quad.m_translate), angle, {0.f, 0.f, 1.f}), quad.m_scale); //!< Translate, Rotate on Z, scale

		s_data->shader->uploadInt("u_texData", 0); //!< Upload texture data
		s_data->shader->uploadFloat4("u_tint", tint); //!< Upload Tint
		s_data->shader->uploadMat4("u_model", s_data->model); //!< Upload model matrix

		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr); //!< Draw quads
	}

	void Renderer2D::submit(char cha, const glm::vec2 & position, float & advance, const glm::vec4& tint)
	{
		// Get glyph from freetype
		if (FT_Load_Char(s_data->fontFace, cha, FT_LOAD_RENDER)) { Logger::error("Could not load glyph for character {0}", cha); } //!< Load glyph & error if cannot load
		else
		{
			// Glyph Data
			uint32_t glyphWidth = s_data->fontFace->glyph->bitmap.width; //!< Glyph width
			uint32_t glyphHeight = s_data->fontFace->glyph->bitmap.rows; //!< Glyph Height
			glm::vec2 glyphSize(glyphWidth, glyphHeight); //!< Size of glyph (Width & Height)
			glm::vec2 glyphBearing(s_data->fontFace->glyph->bitmap_left, -s_data->fontFace->glyph->bitmap_top); //!< Glyph Bearing

			// Advance
			advance = static_cast<float>(s_data->fontFace->glyph->advance.x >> 6); //!< Advance calculation in x

			// Calculate Quad for glyph
			glm::vec2 glyphHalfExtents = glm::vec2(s_data->fontTexture->getWidthf() * 0.5f, s_data->fontTexture->getHeightf() * 0.5f); //!< Half Extents Height & Width
			glm::vec2 glyphCentre = (position + glyphBearing) + glyphHalfExtents; //!< Glyph Position calc (Top Left + Half Extents)
		
			Quad quad = Quad::createCentreHalfExtents(glyphCentre, glyphHalfExtents); //!< Creating the half extents
			
			RtoRGBA(s_data->fontFace->glyph->bitmap.buffer, glyphWidth, glyphHeight); //!< RGBA Buffer
			s_data->fontTexture->edit(0, 0, s_data->glyphBufferDims.x, s_data->glyphBufferDims.y, s_data->glyphBuffer.get()); //!< Edit texture (Offset.x, Offset.y, Height, Width, Data)

			// Submit Quad (Temporary)
			submit(quad, tint, s_data->fontTexture); //!< Submitting the quad
		}
	}

	void Renderer2D::submit(const char * string, const glm::vec2 & position, const glm::vec4& tint)
	{
		uint32_t stringLength = strlen(string); //!< Length of the string
		float advance = 0.f, x = position.x; //!< Advance is equal to 0 & x is the position on x axis
		for (int32_t i = 0; i < stringLength; i++)
		{
			submit(string[i], { x, position.y }, advance, tint); //!< Submit the string, the position of the string and the tint of the string (colour)
			x += advance; //!< x + advance(0)
		}
	}

	void Renderer2D::end()
	{

	}

	//void Renderer2D::getTextSize(const char * text)
	//{
	//	glm::ivec2 result(0);
	//	uint32_t length = strlen(text);
	//
	//	for (int32_t i = 0; i < length; i++)
	//	{
	//		//GlyphData& gd = s_data->glyphData.at(text[i] - s_data->firstGlyph);
	//		//result.x += gd.advance;
	//		//result.y = std::max(result.y, static_cast<int>(gd.size.y));
	//	}
	//
	//	//return result;
	//
	//}



	void Renderer2D::RtoRGBA(unsigned char * RBuffer, uint32_t width, uint32_t height)
	{
		memset(s_data->glyphBuffer.get(), 0, s_data->glyphBufferSize); //!< Blanking out glyph buffer

		unsigned char* pWalker = s_data->glyphBuffer.get(); //!< Unsigned char for glyphBuffer
		for (int32_t i = 0; i < height; i++)
		{
			for (int32_t j = 0; j < width; j++) //!< Across then down
			{
				*pWalker = 255; pWalker++; //!< R Set to White, then move to G
				*pWalker = 255; pWalker++; //!< G Set to White, then move to B
				*pWalker = 255; pWalker++; //!< B Set to White, then move to A
				*pWalker = *RBuffer; //!< Alpha Channel Set
				pWalker++; //!< Go to R of next pixel
				RBuffer++; //!< Next Monochrome pixel
			}
			pWalker += (s_data->glyphBufferDims.x - width) * 4; //!< glyphBufferDim - width multiplied by 4 (4 Channels)
		}
	}

	Quad Quad::createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents)
	{
		Quad result; //!< Result is a quad

		result.m_translate = glm::vec3(centre, 0.f); //!< Transform
		result.m_scale = glm::vec3(halfExtents * 2.f, 1.f); //!< Scale
		
		return result; //!< Return result
	}

	Quad Quad::createCentreHalfExtents(const glm::vec2& centre, float halfExtents)
	{ 
		Quad result; //!< Result is a quad
		result.m_translate = glm::vec3(centre, 0.f); //!< Transform
		result.m_scale = glm::vec3(halfExtents * 2.f, halfExtents * 2.f, 1.f); //!< Scale
		return result;
	}

	Quad Quad::createTopLeftSize(const glm::vec2 & topLeft, const glm::vec2 & size)
	{
		Quad result; //!< Result is a quad
		result.m_translate = glm::vec3(topLeft.x + (size.x / 2), topLeft.y + (size.y / 2), 0.f); //!< Transform
		result.m_scale = glm::vec3(size, 1.f); //!< Scale
		return result;
	}

	Quad Quad::createTopLeftSize(const glm::vec2 & topLeft, float size)
	{
		Quad result; //!< Result is a quad
		result.m_translate = glm::vec3(topLeft.x + (size / 2), topLeft.y + (size / 2), 0.f); //!< Transform
		result.m_scale = glm::vec3(size, size, 1.f); //!< Scale
		return result;
	}

	Quad Quad::createTopLeftBottomRight(const glm::vec2 & topLeft, const glm::vec2 & bottomRight)
	{
		Quad result; //!< Result is a quad
		glm::vec2 size(bottomRight.x - topLeft.x, bottomRight.y - topLeft.y); //!< Transform
		return Quad::createTopLeftSize(topLeft, size); //!< Scale
	}
}