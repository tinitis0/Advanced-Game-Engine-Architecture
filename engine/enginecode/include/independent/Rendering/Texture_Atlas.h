/*! \file Texture_Atlas.h*/
#pragma once

#include <vector>
#include "Rendering/SubTexture.h"

namespace Engine
{
	struct SimpleRect { uint32_t x, y, w, h; }; //!< Struct for x, y, width & height
	
	/*! \class TextureAtlas */
	class TextureAtlas
	{	
	public:
		TextureAtlas(glm::ivec2 size = { 4096, 4096 }, uint32_t channels = 4, uint32_t reserved = 32); //!< Constructor which takes a texture size of 4096 x 4096 & has 4 channels RGBA
		bool add(const char * filepath, SubTexture& result); //!< Setter to add subtexture to file
		bool add(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data, SubTexture& result); //!< Setter to add subtexture via data
		inline uint32_t getChannels() const { return m_baseTexture->getChannels(); } //!< Getter for channels
		inline std::shared_ptr<Textures> getBaseTexture() const { return m_baseTexture; } //!< Getter for the base texture
		inline uint32_t getID() const { return m_baseTexture->getRenderID(); } //!< Getter for the texture ID
	private:
		std::vector<SimpleRect> m_spaces; //!< Gaps which can be filled
		std::shared_ptr<Textures> m_baseTexture; //!< Texture which holds all subtexture pixel data
	};
}