/*! \file Renderer3D.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "Platform/Renderer/3D_Renderer.h"

namespace Engine
{
	std::shared_ptr<Renderer3D::InternalData> Renderer3D::s_data = nullptr;


	void Renderer3D::init()
	{
		s_data.reset(new InternalData); //!< Creates new internal data

		unsigned char whitePx[4] = { 255,255,255,255 }; //!< White pixel
		s_data->defaultTexture.reset(Textures::create(1, 1, 4, whitePx)); //!< Width of 1, Height of 1 and 4 Channels. Default Texture
	
		s_data->defaultTint = { 1.f, 1.f, 1.f, 1.f }; //!< Default tint is no tint
	}

	void Renderer3D::begin(const SceneWideUniforms & swu)
	{
		s_data->sceneWideUniforms = swu; //!< Setting scene uniforms in data
	}

	void Renderer3D::submit(const std::shared_ptr<vertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4 & transform)
	{
		// Shader Binding
		glUseProgram(material->getShader()->getRenderID()); //!< Use shader set in material
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// Applying sceneWideUniforms
		for (auto& dataPair : s_data->sceneWideUniforms)
		{
			const char* nameOfUniform = dataPair.first; //!< Uniform name
			dataPair.second->attachShaderBlock(material->getShader(), nameOfUniform); //!< Attach shader block
		}

		// Apply material uniforms
		
		// Model
		material->getShader()->uploadMat4("u_model", transform); //!< Upload model matrix
		
		// Texture
		if (material->isFlagSet(Material::main_texture)) { glBindTexture(GL_TEXTURE_2D, material->getMainTexture()->getRenderID()); }//!< If texture flag is set bind the texture
		else { glBindTexture(GL_TEXTURE_2D, s_data->defaultTexture->getRenderID()); } //!< Else set the default texture (White)
		material->getShader()->uploadInt("u_texData", 0); //!< Upload texture data

		// Tint
		if (material->isFlagSet(Material::flag_tint)) { material->getShader()->uploadFloat4("u_tint", material->getTint()); }//!< If texture flag is set bind the texture
		else { material->getShader()->uploadFloat4("u_tint", s_data->defaultTint); } //!< Else set the default texture (White)
	
		// Bind Geometry
		glBindVertexArray(geometry->getRenderID()); //!< Binding vertex array
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->getIndexBuffer()->getRenderID()); //!< Binding buffer

		// Submit the draw call
		glDrawElements(GL_TRIANGLES, geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr); //!< Draw
	}

	void Renderer3D::end()
	{
		s_data->sceneWideUniforms.clear(); //!< Clearing the scene wide uniforms in the data
	}

}