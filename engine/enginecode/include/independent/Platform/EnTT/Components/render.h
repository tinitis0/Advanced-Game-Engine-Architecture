#pragma once

#include "Platform/Renderer/3D_Renderer.h"
#include "systems/Logger.h"
#include "Rendering/Textures.h"
#include "Rendering/VertexNormalised.h"
namespace Engine
{
	class RenderComponent
	{
	public:

		RenderComponent(std::shared_ptr<vertexArray>& pGeometry, std::shared_ptr<Shader>& shader, std::shared_ptr<Textures> texture, uint32_t type) { geometry = pGeometry; material.reset(new Material(shader, texture)); geometryType = type; } //!< Constructor that takes a VAO, shader, texture and type
		
		RenderComponent(std::vector<VertexNormalised>& vertices, std::vector<uint32_t>& indices, std::shared_ptr<Material>& p_material, uint32_t type) //!< Constructor that takes the vertices, indecis, material and type
		{

			std::shared_ptr<vertexArray> meshVAO; //!< mesh Vertex array object is an OpenGL vertex array
			std::shared_ptr<vertexBuffer> meshVBO; //!< mesh vertex buffer object is an OpenGL vertex buffer
			std::shared_ptr<indexBuffer> meshIBO; //!< mesh index buffer object is an OpenGL index buffer

			meshVAO.reset(vertexArray::create()); //!< Resetting mesh vertex array object with a new vertex array

			meshVBO.reset(vertexBuffer::create(vertices.data(), sizeof(VertexNormalised) * vertices.size(), VertexNormalised::getLayout())); //!< Resetting mesh vertex buffer object with a new vertex buffer and parameters

			meshIBO.reset(indexBuffer::create(indices.data(), indices.size())); //!< Resetting mesh index buffer with cube vertices and 36 as indices count

			meshVAO->addVertexBuffer(meshVBO); //!< Adding a vertex buffer to mesh vertex array
			meshVAO->setIndexBuffer(meshIBO); //!< Setting index buffer as meshIBO
			geometry = meshVAO; //!< Set the geometry to the new VAO
			material = p_material; //!< Set the material to the given material
			geometryType = type; //!< Assign the geometry type for saving
		}

		RenderComponent(std::shared_ptr<vertexArray>& pGeometry, std::shared_ptr<Material> pMaterial, uint32_t type) { geometry = pGeometry; material = pMaterial; geometryType = type; } //!< Constructor that takes a VAO, material and type

		RenderComponent(std::shared_ptr<vertexArray>& pGeometry, std::shared_ptr<Shader>& shader, std::shared_ptr<Material> Material, uint32_t type) { geometry = pGeometry; material = Material; geometryType = type; } //!< Constructor that takes a VAO, shader, material and type

		std::shared_ptr<vertexArray> geometry; //!< VAO to render
		std::shared_ptr<Material> material; //!< Material to render with

		std::shared_ptr<Material> getMaterial() { return material; }; //!< Getter for the material, to apply tints in imGui
		uint32_t getType() { return geometryType; } //Getter for the types (0 = sphere, 1 = cube, 2 = pyramid)
		uint32_t geometryType; //!< geometry type is sort of like an index of the VAOs we have

	};

}