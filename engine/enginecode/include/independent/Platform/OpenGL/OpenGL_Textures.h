/*! \file OpenGL_Textures.h */
#pragma once
#include <cstdint>
#include "Rendering/Textures.h"

namespace Engine
{
	/*! \class OpenGL_Textures 
	* For setting textures without the need of it being in Application.cpp
	*/
	class OpenGL_Textures : public Textures
	{
	public:
		OpenGL_Textures(const char * filepath); //!< Contructor that takes the filepath on the texture
		OpenGL_Textures(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data); //!, Constructor to craete with data
		~OpenGL_Textures(); //!< Destructor
		void edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char * data); //!< Edit the texture
		virtual inline uint32_t getRenderID() const override { return m_OpenGL_ID; } //!< Getter for OpenGL_ID
		inline uint32_t getWidth() { return m_width; } //!< Getter for width data
		inline uint32_t getHeight() { return m_height; } //!< Getter for height data
		inline uint32_t getChannels() { return m_channels; } //!< Getter for colour channels data
		// Float
		inline uint32_t getWidthf() { return static_cast<float> (m_width); } //!< Getter for width data as float
		inline uint32_t getHeightf() { return static_cast<float> (m_height); } //!< Getter for height data as float
	private:
		uint32_t m_OpenGL_ID; //!< OpenGL ID used e.g. letterTexture
		uint32_t m_width; //!< Width data
		uint32_t m_height; //!< Height data
		uint32_t m_channels; //!< Channels data
		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data); //!< Initialise 
	};
}