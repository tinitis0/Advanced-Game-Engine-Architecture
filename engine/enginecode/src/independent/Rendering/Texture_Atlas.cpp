/*! \file TextureAtlas.cpp */

#include "engine_pch.h"
#include "Rendering/Texture_Atlas.h"
#include <stb_image.h>

namespace Engine
{
	TextureAtlas::TextureAtlas(glm::ivec2 size, uint32_t channels, uint32_t reserved)
	{
		m_baseTexture.reset(Textures::create(size.x, size.y, channels, nullptr)); //!< Create Base Texture
	
		m_spaces.reserve(reserved); //!< Reserve Space
		m_spaces.push_back({ 0, 0, static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y) }); //!< Pushback space
	}

	bool TextureAtlas::add(const char * filepath, SubTexture & result)
	{
		int32_t w, h, c; //!< Width, Height, Channels
		unsigned char * data = stbi_load(filepath, &w, &h, &c, static_cast<int>(getChannels())); //!< Data is the filepath, width, height, channels and desired channels

		if (data)
		{
			return add(w, h, c, data, result); //!< Add data
		}

		return false;
	}

	bool TextureAtlas::add(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data, SubTexture & result)
	{
		if (channels != getChannels()) return false; //!< Check if channels match
		
		for (auto it = m_spaces.begin(); it != m_spaces.end(); ++it)
		{
			SimpleRect& space = *it;
			// Does texture fit the available space
			if (width < space.w && height < space.h)
			{
				// Texture fits space
				m_baseTexture->edit(space.x, space.y, width, height, data); //!< Edit the texture

				// Subtexture result
				glm::vec2 UVStart(static_cast<float>(space.x) / m_baseTexture->getWidthf(), static_cast<float>(space.y) / m_baseTexture->getHeightf()); //!< UV Start Calculation
				glm::vec2 UVEnd(static_cast<float>(space.x + space.w) / m_baseTexture->getWidthf(), static_cast<float>(space.y + space.h) / m_baseTexture->getHeightf()); //!< UV End Calculation
				result = SubTexture(m_baseTexture, UVStart, UVEnd); //!< Result

				// Sort Remaining Space
				// Texture matches width & height
				if (width == space.w && height == space.h)
				{
					m_spaces.erase(it); //!< Erase Space
					return true;
				}
				// Texture width matches space width, however height does not match space height - Horizontal Split
				else if (width == space.w)
				{
					space.y += height; //!< Add height of texture to y
					space.h -= height; //!< Subtract height of texture from height
					return true;
				}
				// Texture height matches space height, however width does not match space width - Vertically Split
				else if (height == space.h)
				{
					space.x += width; //!< Add width of texture to x
					space.w -= width; //!< Subtract width of texture from width
					return true;
				}
				// Texture height & width do not match - split horizontally and vertically
				else
				{
					m_spaces.push_back({ space.x, space.y + height, width,space.h - height }); //!< Pushback
					space.x += width; //!< Add width of texture to x
					space.w -= width; //!< Subtract width of texture from width
					return true;
				}


			} //!< If width & height of texture is less than the spac
		} //!< Find Space to fill

		return false;
	}
}