/*! \file OpenGL_Textures.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "Platform/OpenGL/OpenGL_Textures.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Engine
{
	OpenGL_Textures::OpenGL_Textures(const char * filepath)
	{

		int width, height, channels; //!< Data for Width, Height & Channel
		unsigned char *data = stbi_load(filepath, &width, &height, &channels, 0); //!< Data of the Texture

		if (data) init(width, height, channels, data);
		
		stbi_image_free(data); //!< Free image data

	}
	OpenGL_Textures::OpenGL_Textures(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data)
	{
		init(width, height, channels, data); //!< Initialise with width, height, channels and data
	}

	OpenGL_Textures::~OpenGL_Textures()
	{
		glDeleteTextures(1, &m_OpenGL_ID); //!< Delete texture based off OpenGL ID
	}
	void OpenGL_Textures::edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char * data)
	{
		glBindTexture(GL_TEXTURE_2D, m_OpenGL_ID); //!< Generate letter texture
		if (data)
		{
			if (m_channels == 3) glTextureSubImage2D(m_OpenGL_ID, 0, xOffset, yOffset, width, height, GL_RGB, GL_UNSIGNED_BYTE, data); //!< Create 2D texture, level 0, RGB Texture, No border, Unsigned byte format
			else if (m_channels == 4) glTextureSubImage2D(m_OpenGL_ID, 0, xOffset, yOffset, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data); //!< 4 Channels (RGBA)
		}
	}
	void OpenGL_Textures::init(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data)
	{
		glGenTextures(1, &m_OpenGL_ID); //!< Generate letter texture
		glBindTexture(GL_TEXTURE_2D, m_OpenGL_ID); //!< Bind texture
		// How to wrap
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //!< Clamp to edge
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //!< Clamp to edge
		// How to decide subpixel filtering 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //!< Linear Filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //!< Linear Filtering

		if (channels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //!< Create 2D texture, level 0, RGB Texture, No border, Unsigned byte format
		else if (channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //!< 4 Channels (RGBA)
		else return;
		glGenerateMipmap(GL_TEXTURE_2D); //!< Generate MipMap of the texture
	
		m_width = width;
		m_height = height;
		m_channels = channels;
	}
}
