/*! \file Textures.h */
#pragma once
#include <cstdint>

namespace Engine
{
	/*! \class Textures */
	class Textures
	{
	public:
		virtual ~Textures() {}; //!< Destructor
		virtual void edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char * data) = 0; //!< Edit the texture
		virtual inline uint32_t getRenderID() const = 0; //!< Getter for OpenGL_ID
		virtual inline uint32_t getWidth() = 0; //!< Getter for width data
		virtual inline uint32_t getHeight() = 0; //!< Getter for height data
		virtual inline uint32_t getChannels() = 0; //!< Getter for colour channels data
		// Float
		virtual inline uint32_t getWidthf() = 0; //!< Getter for width data as float
		virtual inline uint32_t getHeightf() = 0; //!< Getter for height data as float

		static Textures* create(const char * filepath); //< Create via filepath
		static Textures* create(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data); //!< Create from scratch

	};
}