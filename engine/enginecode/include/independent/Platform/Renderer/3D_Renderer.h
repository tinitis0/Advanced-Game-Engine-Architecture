/*! \file 3D_Renderer.h */
#pragma once

#include "RendererCommon.h"

namespace Engine
{	
	/*! \class Material
	*  \brief Data associated with the shader
	*/
	class Material
	{
	public:
		Material(std::shared_ptr<Shader>& shader) : 
			m_shader(shader), m_flags(0), m_textures(nullptr), m_colourTint(glm::vec4(0.f)) 
		{} //!< Constructor that takes the shader
		
		Material(uint32_t flags, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Textures>& texture, const glm::vec4& tint) :
			m_shader(shader), m_textures(texture), m_colourTint(tint)
		{
			setFlag(main_texture | flag_tint);
		}
		
		Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Textures>& texture) :
			m_shader(shader), m_textures(texture), m_colourTint(glm::vec4(0.f))
		{
			setFlag(main_texture);
		}
		
		Material(const std::shared_ptr<Shader>& shader, const glm::vec4& tint) :
			m_shader(shader), m_textures(nullptr), m_colourTint(tint)
		{
			setFlag(flag_tint);
		}
		
		
		inline std::shared_ptr<Shader> getShader() const { return m_shader; } //!< Getter for the shader
		inline std::shared_ptr<Textures> getMainTexture() const { return m_textures; } //!< Getter for main texture
		inline glm::vec4 getTint() const { return m_colourTint; } //!< Getter for the tint

		void setMainTexture(const std::shared_ptr<Textures>& texture) { m_textures = texture; setFlag(main_texture); } //!< Setter for the main texture and the flag for the texture
		void setTint(const glm::vec4& tint) { m_colourTint = tint; setFlag(flag_tint); } //!< Setter for the tint and the flag tint
		bool isFlagSet(uint32_t flag) const { return m_flags & flag; } //!< Is a flag set?

		constexpr static uint32_t main_texture = 1 << 0; //!< 00000001
		constexpr static uint32_t flag_tint = 1 << 1;	//!< 00000010
	private:
		uint32_t m_flags = 0; //!< Bitfield representation of shader settings
		std::shared_ptr<Shader> m_shader; //!< The shader
		std::shared_ptr<Textures> m_textures; //!< Texture applied
		glm::vec4 m_colourTint; //!< Colour tint to be applied
		void setFlag(uint32_t flag) { m_flags = m_flags | flag; } //!< Setter for flags
	};

	/*! \class Renderer3D																						
	*  \brief Renders 3D geometry instantly 
	*/
	class Renderer3D
	{
	public:
		static void init(); //!< Initialise
		static void begin(const SceneWideUniforms& swu); //!< Begin 3D scene
		static void submit(const std::shared_ptr<vertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4& transform); //!< Submit bit of geometry to be rendered
		static void end(); //!< End current 3D scene
	private:
		struct InternalData
		{
			SceneWideUniforms sceneWideUniforms; //!< Scene Wide Uniforms
			std::shared_ptr<Textures> defaultTexture; //!< Empty Texture
			std::shared_ptr<Shader> shader; //!< Shader Used
			glm::vec4 defaultTint; //!< Default Tint
		};

		static std::shared_ptr<InternalData> s_data; //!< Internal Data to the renderer
	};
}