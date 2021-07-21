/*! \file EnTTLayer.cpp */
#include "engine_pch.h"
#include "EnTTLayer.h"
#include "Rendering/VertexNormalised.h"
#include "assimpLoader.h"
#include "core/application.h"
#include "systems/Logger.h"
#include <reactphysics3d/reactphysics3d.h>
#include "core/resources.h"

#include <glm/gtc/type_ptr.hpp>

	EnTTLayer::EnTTLayer(const char* name) : Layer(name), m_registry(Application::getInstance().m_registry), m_entities(Application::getInstance().m_entities) //layer(Layer(name)) used as Layer(name) broke, due to Layer not being a nonstatic member.
	{ 
		auto& window = Application::getInstance().getWindow(); //!< Get the window
		rManager = Application::getInstance().getRM(); //!< Get the resource manager


		FrameBufferLayout FBlayout = { { AttachmentType::Colour, true}, {AttachmentType::Depth, false} };
		textureTarget.reset(FrameBuffer::create({ window->getWidth(), window->getHeight() }, FBlayout));

		defaultFBO.reset(FrameBuffer::createDefault());

		//Application::getInstance().getWorld()->setIsDebugRenderingEnabled(true);
		//Application::getInstance().getWorld()->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);

#pragma region TEXTURES

		
		letterTexture.reset(Textures::create("assets/textures/letterCube.png")); //!< Load Texture
		
		numberTexture.reset(Textures::create("assets/textures/numberCube.png")); //!< Load Texture
		unsigned char whitePx[4] = { 255,255,255,255 }; //!< White pixel
		
		plainWhiteTexture.reset(Textures::create(1, 1, 4, whitePx)); //!< Width of 1, Height of 1 and 4 Channels

#pragma endregion

#pragma region Raw Data

		std::vector<VertexNormalised> cubeVertices(24);

		cubeVertices.at(0) = VertexNormalised({ 0.5f,  0.5f, -0.5f },	Normal::normalise({ 0.f,  0.f, -1.f }),  Normal::normalise({ 0.f,   0.f, }));
		cubeVertices.at(1) = VertexNormalised({ 0.5f, -0.5f, -0.5f },	Normal::normalise({ 0.f,  0.f, -1.f }),  Normal::normalise({ 0.f,   0.5f }));
		cubeVertices.at(2) = VertexNormalised({ -0.5f, -0.5f, -0.5f },  Normal::normalise({ 0.f,  0.f, -1.f }),  Normal::normalise({ 0.33f, 0.5f }));
		cubeVertices.at(3) = VertexNormalised({ -0.5f,  0.5f, -0.5f },  Normal::normalise({ 0.f,  0.f, -1.f }),  Normal::normalise({ 0.33f, 0.f, }));
		cubeVertices.at(4) = VertexNormalised({ -0.5f, -0.5f,  0.5f },  Normal::normalise({ 0.f,  0.f,  1.f }),  Normal::normalise({ 0.33f, 0.5f }));
		cubeVertices.at(5) = VertexNormalised({ 0.5f, -0.5f,  0.5f },	Normal::normalise({ 0.f,  0.f,  1.f }),  Normal::normalise({ 0.66f, 0.5f }));
		cubeVertices.at(6) = VertexNormalised({ 0.5f,  0.5f,  0.5f },	Normal::normalise({ 0.f,  0.f,  1.f }),  Normal::normalise({ 0.66f, 0.f, }));
		cubeVertices.at(7) = VertexNormalised({ -0.5f,  0.5f,  0.5f },  Normal::normalise({ 0.f,  0.f,  1.f }),  Normal::normalise({ 0.33,  0.f, }));
		cubeVertices.at(8) = VertexNormalised({ -0.5f, -0.5f, -0.5f },  Normal::normalise({ 0.f, -1.f,  0.f }),  Normal::normalise({ 1.f,   0.f, }));
		cubeVertices.at(9) = VertexNormalised({ 0.5f, -0.5f, -0.5f },   Normal::normalise({ 0.f, -1.f,  0.f }),  Normal::normalise({ 0.66f, 0.f, }));
		cubeVertices.at(10) = VertexNormalised({ 0.5f, -0.5f,  0.5f },  Normal::normalise({ 0.f, -1.f,  0.f }),  Normal::normalise({ 0.66f, 0.5f }));
		cubeVertices.at(11) = VertexNormalised({ -0.5f, -0.5f,  0.5f }, Normal::normalise({ 0.f, -1.f,  0.f }),  Normal::normalise({ 1.0f,  0.5f }));
		cubeVertices.at(12) = VertexNormalised({ 0.5f,  0.5f,  0.5f },  Normal::normalise({ 0.f,  1.f,  0.f }),  Normal::normalise({ 0.f,   0.5f }));
		cubeVertices.at(13) = VertexNormalised({ 0.5f,  0.5f, -0.5f },  Normal::normalise({ 0.f,  1.f,  0.f }),  Normal::normalise({ 0.f,   1.0f }));
		cubeVertices.at(14) = VertexNormalised({ -0.5f,  0.5f, -0.5f }, Normal::normalise({ 0.f,  1.f,  0.f }),  Normal::normalise({ 0.33f, 1.0f }));
		cubeVertices.at(15) = VertexNormalised({ -0.5f,  0.5f,  0.5f }, Normal::normalise({ 0.f,  1.f,  0.f }),  Normal::normalise({ 0.3f,  0.5f }));
		cubeVertices.at(16) = VertexNormalised({ -0.5f,  0.5f,  0.5f }, Normal::normalise({ -1.f,  0.f,  0.f }), Normal::normalise({ 0.66f, 0.5f }));
		cubeVertices.at(17) = VertexNormalised({ -0.5f,  0.5f, -0.5f }, Normal::normalise({ -1.f,  0.f,  0.f }), Normal::normalise({ 0.33f, 0.5f }));
		cubeVertices.at(18) = VertexNormalised({ -0.5f, -0.5f, -0.5f }, Normal::normalise({ -1.f,  0.f,  0.f }), Normal::normalise({ 0.33f, 1.0f }));
		cubeVertices.at(19) = VertexNormalised({ -0.5f, -0.5f,  0.5f }, Normal::normalise({ -1.f,  0.f,  0.f }), Normal::normalise({ 0.66f, 1.0f }));
		cubeVertices.at(20) = VertexNormalised({ 0.5f, -0.5f, -0.5f },  Normal::normalise({ 1.f,  0.f,  0.f }),  Normal::normalise({ 1.0f,  1.0f }));
		cubeVertices.at(21) = VertexNormalised({ 0.5f,  0.5f, -0.5f },  Normal::normalise({ 1.f,  0.f,  0.f }),  Normal::normalise({ 1.0f,  0.5f }));
		cubeVertices.at(22) = VertexNormalised({ 0.5f,  0.5f,  0.5f },  Normal::normalise({ 1.f,  0.f,  0.f }),  Normal::normalise({ 0.66f, 0.5f }));
		cubeVertices.at(23) = VertexNormalised({ 0.5f, -0.5f,  0.5f },  Normal::normalise({ 1.f,  0.f,  0.f }),  Normal::normalise({ 0.66f, 1.0f }));

		std::vector<VertexNormalised> pyramidVertices(16); //!< pyramidVertices with 16 vertices

		// Pyramid Vertices Vector with all data
		pyramidVertices.at(0) = VertexNormalised({ -0.5f, -0.5f, -0.5f },  Normal::normalise({ 0.8f, 0.2f, 0.8f }), Normal::normalise({ 0.f,   0.f, }));
		pyramidVertices.at(1) = VertexNormalised({ 0.5f, -0.5f, -0.5f },   Normal::normalise({ 0.8f, 0.2f, 0.8f }), Normal::normalise({ 0.f,   0.5f }));
		pyramidVertices.at(2) = VertexNormalised({ 0.5f, -0.5f,  0.5f },   Normal::normalise({ 0.8f, 0.2f, 0.8f }), Normal::normalise({ 0.33f, 0.5f }));
		pyramidVertices.at(3) = VertexNormalised({ -0.5f, -0.5f,  0.5f },  Normal::normalise({ 0.8f, 0.2f, 0.8f }), Normal::normalise({ 0.33f, 0.f, }));
		pyramidVertices.at(4) = VertexNormalised({ -0.5f, -0.5f, -0.5f },  Normal::normalise({ 0.2f, 0.8f, 0.2f }), Normal::normalise({ 0.33f, 0.5f }));
		pyramidVertices.at(5) = VertexNormalised({ -0.5f, -0.5f,  0.5f },  Normal::normalise({ 0.2f, 0.8f, 0.2f }), Normal::normalise({ 0.66f, 0.5f }));
		pyramidVertices.at(6) = VertexNormalised({ 0.0f,  0.5f,  0.0f },   Normal::normalise({ 0.2f, 0.8f, 0.2f }), Normal::normalise({ 0.66f, 0.f, }));
		pyramidVertices.at(7) = VertexNormalised({ -0.5f, -0.5f,  0.5f },  Normal::normalise({ 1.0f, 0.0f, 0.f }),  Normal::normalise({ 0.33,  0.f, }));
		pyramidVertices.at(8) = VertexNormalised({ 0.5f, -0.5f,  0.5f },   Normal::normalise({ 1.0f, 0.0f, 0.f }),  Normal::normalise({ 1.f,   0.f, }));
		pyramidVertices.at(9) = VertexNormalised({ 0.0f,  0.5f,  0.0f },   Normal::normalise({ 1.0f, 0.0f, 0.f }),  Normal::normalise({ 0.66f, 0.f, }));
		pyramidVertices.at(10) = VertexNormalised({ 0.5f, -0.5f,  0.5f },  Normal::normalise({ 0.8f, 0.8f, 0.2f }), Normal::normalise({ 0.66f, 0.5f }));
		pyramidVertices.at(11) = VertexNormalised({ 0.5f, -0.5f, -0.5f },  Normal::normalise({ 0.8f, 0.8f, 0.2f }), Normal::normalise({ 1.0f,  0.5f }));
		pyramidVertices.at(12) = VertexNormalised({ 0.0f,  0.5f,  0.0f },  Normal::normalise({ 0.8f, 0.8f, 0.2f }), Normal::normalise({ 0.f,   0.5f }));
		pyramidVertices.at(13) = VertexNormalised({ 0.5f, -0.5f, -0.5f },  Normal::normalise({ 0.f,  0.2f, 1.0f }), Normal::normalise({ 0.f,   1.0f }));
		pyramidVertices.at(14) = VertexNormalised({ -0.5f, -0.5f, -0.5f }, Normal::normalise({ 0.f,  0.2f, 1.0f }), Normal::normalise({ 0.33f, 1.0f }));
		pyramidVertices.at(15) = VertexNormalised({ 0.0f,  0.5f,  0.0f },  Normal::normalise({ 0.f,  0.2f, 1.0f }), Normal::normalise({ 0.3f,  0.5f }));

		uint32_t pyramidIndices[3 * 6] = //!< 3 by 6 indices in Pyramid									   
		{
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			7, 8, 9,
			10, 11, 12,
			13, 14, 15
		};

		uint32_t cubeIndices[3 * 12] = { //!< 3 by 12 indices in cube
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			12, 13, 14,
			14, 15, 12,
			16, 17, 18,
			18, 19, 16,
			20, 21, 22,
			22, 23, 20
		};
#pragma endregion

#pragma region GL_BUFFERS
		
		std::shared_ptr<vertexBuffer> cubeVBO; //!< Cube vertex buffer object is an OpenGL vertex buffer
		std::shared_ptr<indexBuffer> cubeIBO; //!< Cube index buffer object is an OpenGL index buffer

		cubeVAO.reset(vertexArray::create()); //!< Resetting cube vertex array object with a new vertex array

		cubeVBO.reset(vertexBuffer::create(cubeVertices.data(), sizeof(VertexNormalised) * cubeVertices.size(), VertexNormalised::getLayout())); //!< Resetting cube vertex buffer object with a new vertex buffer and parameters

		cubeIBO.reset(indexBuffer::create(cubeIndices, 36)); //!< Resetting cube index buffer with cube vertices and 36 as indices count

		cubeVAO->addVertexBuffer(cubeVBO); //!< Adding a vertex buffer to vertex array
		cubeVAO->setIndexBuffer(cubeIBO); //!< Setting index buffer as cubeIBO

		std::shared_ptr<vertexArray> pyramidVAO; //!< Pyramid Vertex array object is an OpenGL vertex array
		std::shared_ptr<vertexBuffer> pyramidVBO; //!< Pyramid vertex buffer object is an OpenGL vertex buffer
		std::shared_ptr<indexBuffer> pyramidIBO; //!< Pyramid index buffer object is an OpenGL index buffer

		pyramidVAO.reset(vertexArray::create()); //!< Resetting cube vertex array object with a new vertex array

		pyramidVBO.reset(vertexBuffer::create(pyramidVertices.data(), sizeof(VertexNormalised) * pyramidVertices.size(), VertexNormalised::getLayout())); //!< Resetting pyramid vertex buffer object with a new vertex buffer and parameters

		pyramidIBO.reset(indexBuffer::create(pyramidIndices, 18)); //!< Resetting pyramid index buffer with cube vertices and 18 as indices count

		pyramidVAO->addVertexBuffer(pyramidVBO); //!< Adding a vertex buffer to vertex array
		pyramidVAO->setIndexBuffer(pyramidIBO); //!< Setting index buffer as pyramidIBO


		
#pragma endregion
		
#pragma region SHADERS
		TPShader.reset(Shader::create("./assets/shaders/texturedPhong.glsl"));
#pragma endregion 

#pragma region Materials

		pyramidMat.reset(new Material(TPShader, { 0.f, 1.f, 0.f, 1.f })); //!< Pyramid
#pragma endregion

#pragma region ASSIMP
		Engine::Mesh mesh;
		//Loader::ASSIMPLoad("./assets/models/lettercube/letterCube.obj", mesh);
		Loader::ASSIMPLoad("./assets/models/Golf_Ball_3DS/Golf_Ball_sale.3ds", mesh);

		//Make the mesh into a vertex array. Probably not the most efficient way to do this, but it works.
		std::shared_ptr<vertexBuffer> VBO;//Define the array and buffer objects necessary for a submit to the 3d renderer
		std::shared_ptr<indexBuffer> IBO;

		sphereVAO.reset(vertexArray::create());
		VBO.reset(vertexBuffer::create(mesh.vertices.data(), sizeof(VertexNormalised) * mesh.vertices.size(), VertexNormalised::getLayout()));
		IBO.reset(indexBuffer::create(mesh.indices.data(), mesh.indices.size()));
		sphereVAO->addVertexBuffer(VBO);
		sphereVAO->setIndexBuffer(IBO);
		rManager->sphereVAO = sphereVAO;
		//Loader::ASSIMPLoad("./assets/models/bob/boblampclean.md5mesh", mesh);
#pragma endregion




		m_entities.resize(200);

		for (int i = 0; i < 31; i++) //!< Create the needed entities
		{
			m_entities[i] = m_registry.create();
		}

		m_registry.emplace<RootComponent>(m_entities[0]);

		//Give the entities their names
		//Label Components////////////////////////////////////////
		m_registry.emplace<LabelComponent>(m_entities[0],  "BallRoot");
		m_registry.emplace<LabelComponent>(m_entities[1],  "Ball");

		//Level 1:
		m_registry.emplace<LabelComponent>(m_entities[3],  "Floor");
		m_registry.emplace<LabelComponent>(m_entities[4],  "Left Wall");
		m_registry.emplace<LabelComponent>(m_entities[5],  "Right Wall");
		m_registry.emplace<LabelComponent>(m_entities[6],  "Back Wall");
		m_registry.emplace<LabelComponent>(m_entities[7],  "Front Wall");
		m_registry.emplace<LabelComponent>(m_entities[8],  "Hole");
		m_registry.emplace<LabelComponent>(m_entities[9], "Flag");
		m_registry.emplace <LabelComponent>(m_entities[10], "Arch left");
		m_registry.emplace <LabelComponent>(m_entities[11], "Arch top");
		m_registry.emplace <LabelComponent>(m_entities[12], "Arch right");
		m_registry.emplace <LabelComponent>(m_entities[13], "FallOffHazard");

		//Level 2:
		m_registry.emplace<LabelComponent>(m_entities[14], "Level2Floor");
		m_registry.emplace<LabelComponent>(m_entities[15], "Back wall");
		m_registry.emplace<LabelComponent>(m_entities[16], "Left wall 1");
		m_registry.emplace<LabelComponent>(m_entities[17], "Right wall 1");
		m_registry.emplace<LabelComponent>(m_entities[18], "Left wall 2");
		m_registry.emplace<LabelComponent>(m_entities[19], "Right wall 2");
		m_registry.emplace<LabelComponent>(m_entities[20], "Rotatedwall");
		m_registry.emplace<LabelComponent>(m_entities[21], "Hole2");
		m_registry.emplace<LabelComponent>(m_entities[22], "Level2FinalWall");

		//Level 3:
		m_registry.emplace<LabelComponent>(m_entities[23], "Level3Floor");
		m_registry.emplace<LabelComponent>(m_entities[24], "LeftWallLvl3");
		m_registry.emplace<LabelComponent>(m_entities[25], "RightWallLvl3");
		m_registry.emplace<LabelComponent>(m_entities[26], "BackWallLvl3");
		m_registry.emplace<LabelComponent>(m_entities[27], "FrontWallLvl3");
		m_registry.emplace<LabelComponent>(m_entities[28], "Hole3");
		m_registry.emplace<LabelComponent>(m_entities[29], "RampLvl3");
		m_registry.emplace<LabelComponent>(m_entities[30], "JumpWallLvl3");

		//Tags, no longer used
		//m_registry.emplace<TagComponent>(m_entities[1], "Ball");
		//for (int i = 3; i < 8; i++)
		//{
		//	m_registry.emplace<TagComponent>(m_entities[i], "Course");
		//}
		//m_registry.emplace<TagComponent>(m_entities[8], "Hole");
		//m_registry.emplace<TagComponent>(m_entities[9], "Hole");
		//m_registry.emplace<TagComponent>(m_entities[10], "Decoration");
		//m_registry.emplace<TagComponent>(m_entities[11], "Decoration");
		//m_registry.emplace<TagComponent>(m_entities[12], "Decoration");
		

		//Render Components///////////////////////////////////////
		//m_registry.emplace<RenderComponent>(m_entities[0], pyramidVAO, TPShader, pyramidMaterial);

		m_registry.emplace<RenderComponent>(m_entities[1], mesh.vertices, mesh.indices, mesh.material, 0); //Ball
		//Level 1:
		m_registry.emplace<RenderComponent>(m_entities[3], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Level 1 floor
		m_registry.get<RenderComponent>(m_entities[3]).getMaterial()->setTint(glm::vec4{ 0.1f, 0.8f, 0.1f, 1.0f }); //Set the floor to green
		m_registry.emplace<RenderComponent>(m_entities[4], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Left wall
		m_registry.emplace<RenderComponent>(m_entities[5], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Right wall
		m_registry.emplace<RenderComponent>(m_entities[6], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Back wall
		m_registry.emplace<RenderComponent>(m_entities[7], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Front wall
		m_registry.emplace<RenderComponent>(m_entities[8], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Hole 1
		m_registry.get<RenderComponent>(m_entities[8]).getMaterial()->setTint(glm::vec4{ 0.f, 0.f, 0.f, 1.0f }); //!< Make the hole black
		m_registry.emplace<RenderComponent>(m_entities[9], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Flag
		m_registry.emplace<RenderComponent>(m_entities[10], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Left of the arch
		m_registry.emplace<RenderComponent>(m_entities[11], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Top of the arch
		m_registry.emplace<RenderComponent>(m_entities[12], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Right of the arch
		for (int i = 4; i < 8; i++)
		{
			m_registry.get<RenderComponent>(m_entities[i]).getMaterial()->setTint(glm::vec4{ 0.76f, 0.39f, 0.157f, 1.0f }); //!< Make the walls brown
		}

		//Level 2:
		m_registry.emplace<RenderComponent>(m_entities[14], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Floor
		m_registry.get<RenderComponent>(m_entities[14]).getMaterial()->setTint(glm::vec4{ 0.1f, 0.8f, 0.1f, 1.0f }); //Set the floor to green
		m_registry.emplace<RenderComponent>(m_entities[15], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Back wall
		m_registry.emplace<RenderComponent>(m_entities[16], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Left wall 1
		m_registry.emplace<RenderComponent>(m_entities[17], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Right wall 1
		m_registry.emplace<RenderComponent>(m_entities[18], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Left wall 2 (Back wall)
		m_registry.emplace<RenderComponent>(m_entities[19], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Right wall 2 (Wall on the right) 
		m_registry.emplace<RenderComponent>(m_entities[20], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Rotated wall
		m_registry.emplace<RenderComponent>(m_entities[21], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Hole 2
		m_registry.get<RenderComponent>(m_entities[21]).getMaterial()->setTint(glm::vec4{ 0.f, 0.f, 0.f, 1.0f }); //!< Make the hole black
		m_registry.emplace<RenderComponent>(m_entities[22], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Final wall (Level 2)
		for (int i = 15; i < 21; i++)
		{
			m_registry.get<RenderComponent>(m_entities[i]).getMaterial()->setTint(glm::vec4{ 0.76f, 0.39f, 0.157f, 1.0f }); //!< Make the walls brown
		}
		m_registry.get<RenderComponent>(m_entities[22]).getMaterial()->setTint(glm::vec4{ 0.76f, 0.39f, 0.157f, 1.0f }); //!< Make the walls brown
																									  
		//Level 3:
		m_registry.emplace<RenderComponent>(m_entities[23], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Floor
		m_registry.get<RenderComponent>(m_entities[23]).getMaterial()->setTint(glm::vec4{ 0.1f, 0.8f, 0.1f, 1.0f }); //!< Set the floor to green
		m_registry.emplace<RenderComponent>(m_entities[24], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Left wall
		m_registry.emplace<RenderComponent>(m_entities[25], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Right wall
		m_registry.emplace<RenderComponent>(m_entities[26], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Back wall
		m_registry.emplace<RenderComponent>(m_entities[27], cubeVAO, TPShader, plainWhiteTexture, 1); //!< FinalWall
		m_registry.emplace<RenderComponent>(m_entities[28], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Hole 3
		m_registry.get<RenderComponent>(m_entities[28]).getMaterial()->setTint(glm::vec4{ 0.f, 0.f, 0.f, 1.0f }); //!< Make the hole black
		m_registry.emplace<RenderComponent>(m_entities[29], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Ramp
		m_registry.get<RenderComponent>(m_entities[29]).getMaterial()->setTint(glm::vec4{ 0.1f, 0.8f, 0.1f, 1.0f }); //!< Set the ramp to be green
		m_registry.emplace<RenderComponent>(m_entities[30], cubeVAO, TPShader, plainWhiteTexture, 1); //!< Jumpable wall
		for (int i = 24; i < 28; i++)
		{
			m_registry.get<RenderComponent>(m_entities[i]).getMaterial()->setTint(glm::vec4{ 0.76f, 0.39f, 0.157f, 1.0f }); //!< Make the walls brown
		}
		m_registry.get<RenderComponent>(m_entities[30]).getMaterial()->setTint(glm::vec4{ 0.76f, 0.39f, 0.157f, 1.0f }); //!< Make the walls brown


		//Transform Components////////////////////////////////////
		//m_registry.emplace<TransformComponent>(m_entities[0], glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f));
		m_registry.emplace<TransformComponent>(m_entities[0], glm::vec3(-8.f, 0.f, -6.f), glm::vec3(0.f), glm::vec3(1.f));
		m_registry.emplace<TransformComponent>(m_entities[1], glm::vec3(0.f, -3.f, -6.f), glm::vec3(0.f), glm::vec3(0.1f));
		m_registry.emplace<TransformComponent>(m_entities[2], glm::vec3(-8.f, 0.f, -6.f), glm::vec3(0.f), glm::vec3(1.f));

		//Level 1:
		m_registry.emplace<TransformComponent>(m_entities[3], glm::vec3(0.f, -4.25f, -18.f), glm::vec3(0.f), glm::vec3(5.f, 1.f, 30.f)); //Floor
		m_registry.emplace<TransformComponent>(m_entities[4],  glm::vec3(-2.375f, -3.5f, -18.f), glm::vec3(0.f), glm::vec3(0.25f, 0.5f, 30.f)); //L wall
		m_registry.emplace<TransformComponent>(m_entities[5],  glm::vec3(2.375f, -3.5f, -18.f), glm::vec3(0.f), glm::vec3(0.25f, 0.5f, 30.f)); //R wall
		m_registry.emplace<TransformComponent>(m_entities[6],  glm::vec3(0.f, -3.5f, -3.125f), glm::vec3(0.f), glm::vec3(5.f, 0.5f, 0.25f)); //Back wall
		m_registry.emplace<TransformComponent>(m_entities[7],  glm::vec3(0.f, -3.5f, -32.875f), glm::vec3(0.f), glm::vec3(5.f, 0.5f, 0.25f)); //Front wall
		m_registry.emplace<TransformComponent>(m_entities[8],  glm::vec3(0.f, -3.8f, -30.f), glm::vec3(0.f), glm::vec3(0.25f)); //hole
		m_registry.emplace<TransformComponent>(m_entities[9],  glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f)); //Flag
		m_registry.emplace<TransformComponent>(m_entities[10], glm::vec3(-2.375f, -1.75f, -15.f), glm::vec3(0.f), glm::vec3(0.25f, 3.f, 0.25f));
		m_registry.emplace<TransformComponent>(m_entities[11], glm::vec3(0.f, -0.5f, -15.f), glm::vec3(0.f), glm::vec3(5.f, 1.f, 0.25f));
		m_registry.emplace<TransformComponent>(m_entities[12], glm::vec3(2.375f, -1.75f, -15.f), glm::vec3(0.f), glm::vec3(0.25f, 3.f, 0.25f));
		m_registry.emplace<TransformComponent>(m_entities[13], glm::vec3(0.f, -5.f, 0.f), glm::vec3(0.f), glm::vec3(0.f));

		//Level 2:
		m_registry.emplace<TransformComponent>(m_entities[14], glm::vec3(12.5f, -4.25f, -18.f), glm::vec3(0.f), glm::vec3(10.f, 1.f, 30.f)); //Floor
		m_registry.emplace<TransformComponent>(m_entities[15], glm::vec3(7.625f, -3.5f, -18.f), glm::vec3(0.f), glm::vec3(0.25f, 0.5f, 30.f)); //L wall
		m_registry.emplace<TransformComponent>(m_entities[16], glm::vec3(12.375f, -3.5f, -15.5f), glm::vec3(0.f), glm::vec3(0.25f, 0.5f, 25.f)); //R wall
		m_registry.emplace<TransformComponent>(m_entities[17], glm::vec3(10.f, -3.5f, -3.125f), glm::vec3(0.f), glm::vec3(5.f, 0.5f, 0.25f)); //Front wall
		m_registry.emplace<TransformComponent>(m_entities[18], glm::vec3(12.5f, -3.5f, -32.875f), glm::vec3(0.f), glm::vec3(10.f, 0.5f, 0.25f)); // Back Wall
		m_registry.emplace<TransformComponent>(m_entities[19], glm::vec3(14.75f, -3.5f, -28.f), glm::vec3(0.f), glm::vec3(5.f, 0.5f, 0.25f)); // Right wall of hole
		m_registry.emplace<TransformComponent>(m_entities[20], glm::vec3(10.f, -3.5f, -30.5f), glm::vec3(0.f, 1.785f, 0.f), glm::vec3(6.75f, 0.5f, 0.25f)); //rotated wall (0.785 is 45 degrees in radians)
		m_registry.emplace<TransformComponent>(m_entities[21], glm::vec3(16.5f, -3.8f, -30.5f), glm::vec3(0.f), glm::vec3(0.25f)); //level 2 hole
		m_registry.emplace<TransformComponent>(m_entities[22], glm::vec3(17.375f, -3.5f, -30.375f), glm::vec3(0.f), glm::vec3(0.25f, 0.5f, 5.f)); //Wall next to level 2 hole
		//m_registry.emplace<TransformComponent>(m_entities[20], glm::vec3(1.f), glm::vec3(0.f), glm::vec3(1.f));

		//Level 3:
		m_registry.emplace<TransformComponent>(m_entities[23], glm::vec3(0.f, -4.25f, -58.f), glm::vec3(0.f), glm::vec3(5.f, 1.f, 30.f)); //Floor
		m_registry.emplace<TransformComponent>(m_entities[24], glm::vec3(-2.375f, -3.5f, -58.f), glm::vec3(0.f), glm::vec3(0.25f, 0.5f, 30.f)); //L wall
		m_registry.emplace<TransformComponent>(m_entities[25], glm::vec3(2.375f, -3.5f, -58.f), glm::vec3(0.f), glm::vec3(0.25f, 0.5f, 30.f)); //R wall
		m_registry.emplace<TransformComponent>(m_entities[26], glm::vec3(0.f, -3.5f, -43.125f), glm::vec3(0.f), glm::vec3(5.f, 0.5f, 0.25f)); //Back wall
		m_registry.emplace<TransformComponent>(m_entities[27], glm::vec3(0.f, -3.5f, -72.875f), glm::vec3(0.f), glm::vec3(5.f, 0.5f, 0.25f)); //Front wall
		m_registry.emplace<TransformComponent>(m_entities[28], glm::vec3(0.f, -3.8f, -70.f), glm::vec3(0.f), glm::vec3(0.25f)); //hole
		m_registry.emplace<TransformComponent>(m_entities[29], glm::vec3(0.f, -3.75f, -53.f), glm::vec3(0.175f, 0.f, 0.f), glm::vec3(3.f, 1.f, 5.f)); //
		m_registry.emplace<TransformComponent>(m_entities[30], glm::vec3(0.f, -3.5f, -65.f), glm::vec3(0.f), glm::vec3(5.f, 0.5f, 0.25f));

		
		//Parent Hierachy/////////////////////////////////////////
		//m_registry.emplace<RelationshipComponent>(m_entities[0]);
		//m_registry.emplace<RelationshipComponent>(m_entities[1]);
		//m_registry.emplace<RelationshipComponent>(m_entities[2]);

		//Hierachy::setChild(m_entities[1], m_entities[0]);

		//Function that adds a collider is at the bottom of this cpp.
		//Rigidbodys and colliders ///////////////////////////////
		addSphereCollider(m_entities[0], RigidBodyType::Dynamic, 0.001f, 0);

		addSphereCollider(m_entities[1], RigidBodyType::Dynamic, 0.1f, 1);
		//addBoxCollider(m_entities[1], RigidBodyType::Dynamic, glm::vec3(0.5f));
		m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->setIsAllowedToSleep(false);

		//Level 1:
		addBoxCollider(m_entities[2], RigidBodyType::Dynamic, glm::vec3(0.5f, 0.5f, 0.5f), 2);
		addBoxCollider(m_entities[3], RigidBodyType::Static, glm::vec3(2.5f, 0.5f, 15.f), 3);
		addBoxCollider(m_entities[4], RigidBodyType::Static, glm::vec3(0.125f, 0.25f, 15.f), 4);
		addBoxCollider(m_entities[5], RigidBodyType::Static, glm::vec3(0.125f, 0.25f, 15.f), 5);
		addBoxCollider(m_entities[6], RigidBodyType::Static, glm::vec3(2.5f, 0.25f, 0.125f), 6);
		addBoxCollider(m_entities[7], RigidBodyType::Static, glm::vec3(2.5f, 0.25f, 0.125f), 7);
		addBoxCollider(m_entities[8], RigidBodyType::Static, glm::vec3(0.125f), 9);
		m_registry.get<BoxColliderComponent>(m_entities[8]).collider->setIsTrigger(true);
		addBoxCollider(m_entities[13], RigidBodyType::Static, glm::vec3(1000.f, 1.f, 1000.f), 10);
		m_registry.get<BoxColliderComponent>(m_entities[13]).collider->setIsTrigger(true);

		//Level 2:
		addBoxCollider(m_entities[14],RigidBodyType::Static, glm::vec3(5.f, 0.5f, 15.f), 11);
		addBoxCollider(m_entities[15],RigidBodyType::Static, glm::vec3(0.125f, 0.25f, 15.f), 12);
		addBoxCollider(m_entities[16],RigidBodyType::Static, glm::vec3(0.125f, 0.25f, 12.5f), 13);
		addBoxCollider(m_entities[17],RigidBodyType::Static, glm::vec3(2.5f, 0.25f, 0.125f), 14);
		addBoxCollider(m_entities[18],RigidBodyType::Static, glm::vec3(5.f, 0.25f, 0.125f), 15);
		addBoxCollider(m_entities[19],RigidBodyType::Static, glm::vec3(2.5f, 0.25f, 0.125f), 16);
		addBoxCollider(m_entities[20],RigidBodyType::Static, glm::vec3(3.375f, 0.25f, 0.125f), 17);
		addBoxCollider(m_entities[21],RigidBodyType::Static, glm::vec3(0.125f), 18); //Hole 2
		addBoxCollider(m_entities[22],RigidBodyType::Static, glm::vec3(0.125f, 0.25f, 2.5f), 19);
		m_registry.get<BoxColliderComponent>(m_entities[21]).collider->setIsTrigger(true);

		//Level 3:
		addBoxCollider(m_entities[23], RigidBodyType::Static, glm::vec3(2.5f, 0.5f, 15.f), 20);
		addBoxCollider(m_entities[24], RigidBodyType::Static, glm::vec3(0.125f, 0.25f, 15.f), 21);
		addBoxCollider(m_entities[25], RigidBodyType::Static, glm::vec3(0.125f, 0.25f, 15.f), 22);
		addBoxCollider(m_entities[26], RigidBodyType::Static, glm::vec3(2.5f, 0.25f, 0.125f), 23);
		addBoxCollider(m_entities[27], RigidBodyType::Static, glm::vec3(2.5f, 0.25f, 0.125f), 24);
		addBoxCollider(m_entities[28], RigidBodyType::Static, glm::vec3(0.125f), 25); //Hole 3
		addBoxCollider(m_entities[29], RigidBodyType::Static, glm::vec3(1.5f, 0.5f, 2.5f), 26);
		addBoxCollider(m_entities[30], RigidBodyType::Static, glm::vec3(2.5f, 0.25f, 0.125f), 27);
		m_registry.get<BoxColliderComponent>(m_entities[28]).collider->setIsTrigger(true);



#pragma region cameras
		glm::mat4* tAddr = &(m_registry.get<TransformComponent>(m_entities[0]).getTransform());

		float aspectRatio = static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight());
		Camera3D.reset(new FreeEuler3DCamera(45.f,aspectRatio, 0.1f, 100.f)); //!< Euler Camera
		Follow3D.reset(new FollowCamera3D(45.f, aspectRatio, 0.1f, 100.f, tAddr, glm::vec3( 0, 1, 4 ))); //!< Follow Camera

		UniformBufferLayout camLayout = { {"u_projection", shaderDataType::Mat4}, {"u_view", shaderDataType::Mat4}, }; //!< Layout set to a Mat4 for projection & a Mat4 for view
		camera3D_UBO.reset(UniformBuffer::create(camLayout)); //!< Reset the camera UBO
		camera3D_UBO->attachShaderBlock(TPShader, "b_camera"); //!< Attach the tpshader to the camera UBO

		UniformBufferLayout lightLayout = { {"u_lightPos", shaderDataType::Float3}, {"u_viewPos", shaderDataType::Float3}, {"u_lightColour", shaderDataType::Float3} };
		lightUBO.reset(UniformBuffer::create(lightLayout)); //!< Reset the light UBO
		lightUBO->attachShaderBlock(TPShader, "b_lights"); //!< Attach the tpshader to the light UBO

		glm::vec3 lightPos(1.0f, 4.0f, 6.0f); //!< Light Position
		glm::vec3 viewPos(0.0f, 0.0f, 0.0f); //!< View Position
		glm::vec3 lightColour(1.f, 1.f, 1.f); //!< Light Colour

		lightUBO->uploadData("u_lightPos", glm::value_ptr(lightPos)); //!< Upload Light Pos
		lightUBO->uploadData("u_viewPos", glm::value_ptr(viewPos)); //!< Upload View Pos
		lightUBO->uploadData("u_lightColour", glm::value_ptr(lightColour)); //!< Upload Light Colour

		m_swu["b_camera"] = camera3D_UBO; //!< Set the scene wide uniform's camera UBO
		m_swu["b_lights"] = lightUBO; //!< Set the scene wide uniform's light UBO

		//activeCam = &Camera3D;
#pragma endregion

	}

	void EnTTLayer::onRender()
	{
		glm::vec3 tmp = Camera3D->getPosition(); //!< Get the camera position
		lightUBO->uploadData("u_viewPos", glm::value_ptr(tmp)); //!< Upload the camera position to the light UBP

		RendererCommon::actionCommand(RendererCommon::setDepthTestEnabled); //!< Enable depth testing
		RendererCommon::actionCommand(RendererCommon::clearColourAndDepth); //!< Clear the colour and depth buffer

		Renderer3D::begin(m_swu); //!< Begin the 3D renderer
		
		auto group = m_registry.group<TransformComponent, RenderComponent>(); //!< Get every entity with a transform and a render component
		for (auto entity : group) //!< Go through each of them
		{
			auto& transform = group.get<TransformComponent>(entity);
			auto& render = group.get<RenderComponent>(entity);

			Renderer3D::submit(render.geometry, render.material, transform.getTransform()); //!< Render them
		}

		////////////////////////////////////////////////////////////////
		auto view = m_registry.view<BoxColliderComponent, RigidBodyComponent, TransformComponent>(); //!< Get every object with a box collider, rigidbody and transform component
		for (auto entity : view) //!< Go through them all
		{
			//auto& col = view.get<BoxColliderComponent>(entity);
			auto& rb = view.get<RigidBodyComponent>(entity);
			auto& transform = view.get<TransformComponent>(entity);

			glm::mat4 t; //!< Get the rigidbody transform
			rb.m_body->getTransform().getOpenGLMatrix(glm::value_ptr(t));

			glm::mat4 s; //!< Get the collider's scale
			s = glm::scale(glm::mat4(1), transform.getScale());

			//renderCommands::getSetWireFrame(); //!< Set to wireframe (DOESNT WORK)
			//Renderer3D::submit(cubeVAO, pyramidMat, t * s); //!< Render their collider
		}

		auto view2 = m_registry.view<SphereColliderComponent, RigidBodyComponent, TransformComponent>(); //!< Get every object with a sphere collider, rigidbody and transform component
		for (auto entity : view2) //!< Loop through them all
		{
			//auto& col = view.get<SphereColliderComponent>(entity);
			auto& rb = view2.get<RigidBodyComponent>(entity);
			auto& transform = view2.get<TransformComponent>(entity);

			glm::mat4 t; //!< Get the rigidbody transform
			rb.m_body->getTransform().getOpenGLMatrix(glm::value_ptr(t));

			glm::mat4 s; //!< Get the collider's scale
			s = glm::scale(glm::mat4(1), transform.getScale());

			//renderCommands::getSetWireFrame(); //!< Set to wireframe (DOESNT WORK)

			//Renderer3D::submit(sphereVAO, pyramidMat, t * s); //!< Render the collider
		}


		Renderer3D::end(); //!< End the 3D renderer
	}

	void EnTTLayer::onUpdate(float timestep)
	{
		bool updateView = false;
		
		if (cam == 0)
		{
			camera3D_UBO->uploadData("u_projection", glm::value_ptr(Camera3D->getCamera().projection)); //!< Upload Projection Data for active camera
			camera3D_UBO->uploadData("u_view", glm::value_ptr(Camera3D->getCamera().view)); //!< Upload View Data for active camera
			glm::vec3 tmp = Camera3D->getPosition(); //!< Get the camera position
			lightUBO->uploadData("u_viewPos", glm::value_ptr(tmp)); //!< Upload the camera position to the shader
			Camera3D->onUpdate(timestep); //!<
		}
		else if (cam == 1)
		{
			camera3D_UBO->uploadData("u_projection", glm::value_ptr(Follow3D->getCamera().projection)); //!< Upload Projection Data for active camera
			camera3D_UBO->uploadData("u_view", glm::value_ptr(Follow3D->getCamera().view)); //!< Upload View Data for active camera
			glm::vec3 tmp = Follow3D->getPosition();
			lightUBO->uploadData("u_viewPos", glm::value_ptr(tmp));
			Follow3D->onUpdate(timestep);
		}

		//Input Polling
		glm::mat4 transform = m_registry.get<TransformComponent>(m_entities[0]).getTransform();
		reactphysics3d::Vector3 right = { transform[0][0], transform[0][1], transform[0][2] }; //!< Right movement
		reactphysics3d::Vector3 forward = { -transform[2][0], -transform[2][1], -transform[2][2] }; //!< Forward Movement

		glm::vec3 dir = Follow3D->getOffset(); //!< Get the camera's offset
		float angle = atan2(dir.z, -dir.x); //!< calculations to find the forward vector
		float riAng = atan2(-dir.z, dir.x); //!< Calculate the right angle
		float mag = sqrtf(dir.x * dir.x + dir.z * dir.z); //!< Get the magnitude
		dir.x = cos(angle) * mag; //!< Find the amount that the ball is facing right (In world space, so 1 is completely and 0.2 would be barely)
		dir.z = -sin(angle) * mag; //!< Find the amount that the ball is facing forwards (In world space, so 1 is completely and 0.2 would be barely)
		dir.y = 0.0f; //!< Y direction is 0 as not affected
		reactphysics3d::Vector3 ballDir = { dir.x, dir.y, dir.z }; //!< Make the direction into a react physics 3d vector3
		dir = glm::cross(glm::vec3(0, 1, 0), -dir); //!< Get the cross product of up and the dir to get the right dir
		reactphysics3d::Vector3 ballRight = { dir.x, dir.y, dir.z }; //!< Make the right dir into a rp3d vector 3, so force can be used with it
		m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->setLinearDamping(reactphysics3d::decimal(0.75f)); //!< Set the linear dampning
		m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->setAngularDamping(reactphysics3d::decimal(0.7f)); //!< Set the angular dampning

		if (m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->getLinearVelocity().length() < 0.1f) //!< If the velocity is really low
		{
			m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->setLinearVelocity(reactphysics3d::Vector3(0.f, 0.f, 0.f)); //!< Set the velocity to 0. (Without this it will never be 0)
			//m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->setAngularVelocity(reactphysics3d::Vector3(0.f, 0.f, 0.f));
			if (rManager->strokes >= rManager->maxStrokes && m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->getLinearVelocity() == reactphysics3d::Vector3(0.f, 0.f, 0.f))
			{
				SetBallToStartPos(); //!< Reset the ball
				rManager->strokes = 0;
			}
			
		}
		if (rManager->nextLevel == true) //!< If the player has completed a level
		{
			SetBallToStartPos(); //!< Move the ball
			rManager->strokes = 0; //!< Reset the strokes
			rManager->nextLevel = false; //!< Set "nextLevel" to false in the resource manager
		}
		else if (rManager->reset == true)
		{
			SetBallToStartPos(); //!< Reset the ball
			rManager->reset = false; //!< Set "reset" to false in the resource manager
		}

		//Logger::info(timestep);
		if (InputPoller::isKeyPressed(NG_KEY_SPACE) && cam == 1 && m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->getLinearVelocity() == reactphysics3d::Vector3(0.f, 0.f, 0.f)) //!< If space is pressed
		{
			if(Shooting == false) //!< Set shooting to true
				Shooting = true;
			if (force >= 1000) //!< If force goes too high
			{
				forceChange = true; //!< Set forceChange to true
				Logger::info("Max force"); //!< Log it
			}
			else if(force <= 0) //!< If force is too low
			{
				forceChange = false; //!< set forceChange to false
				Logger::info("Min force"); //!< Log it
			}
			switch (forceChange) //!< Switch with forceChange's value
			{
			case true: //!< If true
				force -= 250 * timestep; //!< Increase the force
				break;
			case false: //!< If false
				force += 250 * timestep; //!< Decrease the force
				break;
			default:
				force += 250 * timestep; //!< Increase the force by default
				break;
			}
			//Logger::info(force);
			rManager->setForce(force); //!< Update the resource manager's force value
		}
		else if(Shooting == true) //!< If the player has released space after pressing it
		{
			Shooting = false; //!< Set shooting to false

			m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->applyForceToCenterOfMass(ballDir * (force)); //!< apply the force to the ball in the correct direction
			Logger::info("Force is {0}", force); //!< Log the force applied
			force = 0; //!< Set the force to 0
			rManager->setForce(force); //!< Set the rManager's force to 0
			rManager->strokes += 1; //!< Add one to the strokes taken in the resource manager
			Logger::info("Strokes: {0}", rManager->strokes); //!< Log the strokes number
		}

		if (InputPoller::isKeyPressed(NG_KEY_M))
		{
			cam = 0;
		} //!< When M is pressed active camera is the 3D Euler Cam
		if (InputPoller::isKeyPressed(NG_KEY_B))
		{
			cam = 1;
		} //!< When B is pressed active camera is 3D Follow Cam

		NGPhysicsSystem::updateTransforms(); //!< Update the transforms using RP3D
		Hierachy::updateChildren(); //!< update the children
	}

	void EnTTLayer::addBoxCollider(entt::entity & entity, RigidBodyType RBtype, glm::vec3 halfExtents, uint32_t index) //!< Function to add a box collider
	{
		glm::mat4& transform = m_registry.get <TransformComponent>(entity).getTransform();					//!< Get the transform of the object
		RigidBodyComponent rb = m_registry.emplace<RigidBodyComponent>(entity, RBtype, transform, index);   //!< Get and give the object a rigidbody
		m_registry.emplace<BoxColliderComponent>(entity, rb, halfExtents);									//!< Give the object a box collider component
	}

	void EnTTLayer::addSphereCollider(entt::entity & entity, RigidBodyType type, float radius, uint32_t index) //!< Function to add a sphere collider
	{
		glm::mat4& t = m_registry.get<TransformComponent>(entity).getTransform();							//!< Get the transform of the object
		RigidBodyComponent rb = m_registry.emplace<RigidBodyComponent>(entity, type, t, index);				//!< Get and give the object a rigidbody
		m_registry.emplace<SphereColliderComponent>(entity, rb, radius);//glm::vec3(1.f, 1.f, 1.f));		//!< Give the object a sphere collider component
	}

	void EnTTLayer::addSphereTrigger(entt::entity & entity, RigidBodyType type, float radius, uint32_t index) //!< Function to add a sphere trigger
	{
		glm::mat4& t = m_registry.get<TransformComponent>(entity).getTransform();							//!< Get the transform of the object
		RigidBodyComponent rb = m_registry.emplace<RigidBodyComponent>(entity, type, t, index);				//!< Get and give the object a rigidbody
		m_registry.emplace<SphereTriggerComponent>(entity, rb, radius);//glm::vec3(1.f, 1.f, 1.f));			//!< Give the object a sphere trigger component
	}

	void EnTTLayer::SetBallToStartPos()
	{
		rp3d::Transform transf; //!< Predefine the transform
		Logger::info("Resetting!"); //!< Log that the player is being reset
		switch (rManager->getCurrentLevel()) //!< Switch with the current level number
		{
		case 1:
			m_registry.get<TransformComponent>(m_entities[1]).setPosition(glm::vec3(0.f, -3.f, -6.f)); //!< Set the ball's transform component's position
			//glm::vec3 pos = { 0.f, -3.f, -6.f };
			transf = { rp3d::Vector3{ 0.f, -3.f, -6.f }, rp3d::Quaternion::identity() }; //!< Set the RP3D transform to the desired position
			m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->setTransform(transf); //!< Set the rigidbody's transform
			//rManager->strokes = 0;
			break;
		case 2:
			m_registry.get<TransformComponent>(m_entities[1]).setPosition(glm::vec3(10.f, -3.f, -6.f)); //!< Set the ball's transform component's position
			//glm::vec3 pos = { 0.f, -3.f, -6.f };
			transf = { rp3d::Vector3{10.f, -3.f, -6.f}, rp3d::Quaternion::identity() }; //!< Set the RP3D transform to the desired position
			m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->setTransform(transf); //!< Set the rigidbody's transform
			//rManager->strokes = 0;
			break;
		case 3:
			m_registry.get<TransformComponent>(m_entities[1]).setPosition(glm::vec3(0.f, -3.f, -46.f)); //!< Set the ball's transform component's position
			//glm::vec3 pos = { 0.f, -3.f, -6.f }; 
			transf = { rp3d::Vector3{0.f, -3.f, -46.f}, rp3d::Quaternion::identity() }; //!< Set the RP3D transform to the desired position
			m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->setTransform(transf); //!< Set the rigidbody's transform
			//rManager->strokes = 0;
			break;
		default:
			Logger::error("Unknown level!"); //!< Unknown level, dont do anything. Error trapping.
			break;
		}

		m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->setLinearVelocity(reactphysics3d::Vector3(0.f, 0.f, 0.f)); //!< Set the velocity to 0
		m_registry.get<RigidBodyComponent>(m_entities[1]).m_body->setAngularVelocity(reactphysics3d::Vector3(0.f, 0.f, 0.f)); //!< set the angular velocity to 0 too
	}
