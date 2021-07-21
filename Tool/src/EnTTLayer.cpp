/*! \file EnTTLayer.cpp */
#include "engine_pch.h"
#include "EnTTLayer.h"
#include "Rendering/VertexNormalised.h"
#include "imGUILayer.h"

#include "core/application.h"

#include <glm/gtc/type_ptr.hpp>

	EnTTLayer::EnTTLayer(const char* name) : Layer(name), m_registry(Application::getInstance().m_registry), m_entities(Application::getInstance().m_entities) //layer(Layer(name)) used as Layer(name) broke, due to Layer not being a nonstatic member.
	{ 
		auto& window = Application::getInstance().getWindow();

		RM = Application::getInstance().getRM();

		//renderCommands::getSetClearColourCommand(0.7f, 0.7f, 0.7f, 1.0f);

		FrameBufferLayout FBlayout = { { AttachmentType::Colour, true}, {AttachmentType::Depth, false} };
		m_sceneFBO.reset(FrameBuffer::create({ window->getWidth(), window->getHeight() }, FBlayout));
		
		m_defaultFBO.reset(FrameBuffer::createDefault());

#pragma region TEXTURES

	
		letterTexture.reset(Textures::create("assets/textures/letterCube.png")); //!< Load Texture

		numberTexture.reset(Textures::create("assets/textures/numberCube.png")); //!< Load Texture
		unsigned char whitePx[4] = { 255,255,255,255 }; //!< White pixel
;
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
		

		pyramidMaterial.reset(new Material(TPShader, { 0.f, 1.f, 0.f, 1.f })); //!< Pyramid
#pragma endregion

		loadEntities(imGUILayer::loadJSONfile("./assets/json/level.json"));

#pragma region cameras
		glm::mat4* tAddr = &(m_registry.get<TransformComponent>(m_entities[1]).getTransform());

		float aspectRatio = static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight());
		Camera3D.reset(new FreeEuler3DCamera(45.f,aspectRatio, 0.1f, 100.f)); //!< Euler Camera
		Follow3D.reset(new FollowCamera3D(45.f, aspectRatio, 0.1f, 100.f, tAddr, glm::vec3( 0, 1, 4 ))); //!< Follow Camera

		UniformBufferLayout camLayout = { {"u_projection", shaderDataType::Mat4}, {"u_view", shaderDataType::Mat4}, }; //!< Layout set to a Mat4 for projection & a Mat4 for view
		camera3D_UBO.reset(UniformBuffer::create(camLayout));
		camera3D_UBO->attachShaderBlock(TPShader, "b_camera");

		UniformBufferLayout lightLayout = { {"u_lightPos", shaderDataType::Float3}, {"u_viewPos", shaderDataType::Float3}, {"u_lightColour", shaderDataType::Float3} };
		lightUBO.reset(UniformBuffer::create(lightLayout));
		lightUBO->attachShaderBlock(TPShader, "b_lights");

		glm::vec3 lightPos(1.0f, 4.0f, 6.0f); //!< Light Position
		glm::vec3 viewPos(0.0f, 0.0f, 0.0f); //!< View Position
		glm::vec3 lightColour(1.f, 1.f, 1.f); //!< Light Colour

		lightUBO->uploadData("u_lightPos", glm::value_ptr(lightPos)); //!< Upload Light Pos
		lightUBO->uploadData("u_viewPos", glm::value_ptr(viewPos)); //!< Upload View Pos
		lightUBO->uploadData("u_lightColour", glm::value_ptr(lightColour)); //!< Upload Light Colour

		m_swu["b_camera"] = camera3D_UBO;
		m_swu["b_lights"] = lightUBO;

		//activeCam = &Camera3D;
#pragma endregion


	}

	void EnTTLayer::loadEntities(nlohmann::json jsonData)
	{
		m_entities.reserve(5000); // Reserve 5000 slots

		for (int i = 0; i < jsonData.size() - 2; i++) m_entities.push_back(m_registry.create()); // For every bit of JSON data create a registry entry

		m_registry.emplace<RootComponent>(m_entities[0]);

		for (uint32_t i = 0; i < m_entities.size(); i++) // For the size of entitys starting from 0... 
		{
			std::string labelName; // String label name
			auto& label = jsonData[i]["label"]; // label is the JSON data named "label"

			labelName = label.get<std::string>(); // labelName is set to the JSON data label
			m_registry.emplace<LabelComponent>(m_entities[i], labelName); // Emplace the label using this data


			auto& render = jsonData[i]["render"]; // Render is the JSON data for render
			if (render.count("VAO") > 0) // If the JSON data "VAO" is larger than 0...
			{
				switch (render["VAO"].get<uint32_t>()) // Switch case for the uint32_t value
				{
				case 0:

					break;

				case 1:
					m_registry.emplace<RenderComponent>(m_entities[i], cubeVAO, TPShader, plainWhiteTexture, 1); // Emplace the cubeVAO
					break;

				case 2:
					m_registry.emplace<RenderComponent>(m_entities[i], pyramidVAO, TPShader, plainWhiteTexture, 2); // Emplace using the pyramidVAO
					break;
				default:
					Logger::error("No Number Found!");
					break;
				}
				
			}

			glm::vec3 loadedPosition; // Vector3 for the loaded position
			glm::vec3 loadedRotation; // Vector3 for the loaded rotation
			glm::vec3 loadedScale; // Vector3 for the loaded scale
			auto& entity = jsonData[i]["transform"]; // entity is the JSON data transform
			if (entity.count("pos") > 0) // If the entity count for pos is bigger than 0...
			{
				auto& position = entity["pos"]; // psoition is the JSON data set under pos
				if (position.count("x") > 0) loadedPosition.x = position["x"].get<float>(); // Load the X transform data
				if (position.count("y") > 0) loadedPosition.y = position["y"].get<float>(); // Load the Y transform data
				if (position.count("x") > 0) loadedPosition.z = position["z"].get<float>(); // Load the Z transform data
			}
			
			if (entity.count("scale") > 0) // If the entity count for scale is bigger than 0...
			{
				auto& scale = entity["scale"];
				if (scale.count("x") > 0) loadedScale.x = scale["x"].get<float>(); // Load the X scale data
				if (scale.count("y") > 0) loadedScale.y = scale["y"].get<float>(); // Load the Y scale data
				if (scale.count("z") > 0) loadedScale.z = scale["z"].get<float>(); // Load the Z scale data
			}
			
			if (entity.count("rotation") > 0) // If the entity count for rotation is bigger than 0...
			{
				auto& rotation = entity["rotation"];
				if (rotation.count("x") > 0) loadedRotation.x = rotation["x"].get<float>(); // Load the X rotation data
				if (rotation.count("y") > 0) loadedRotation.y = rotation["y"].get<float>();	// Load the Y rotation data
				if (rotation.count("z") > 0) loadedRotation.z = rotation["z"].get<float>();	// Load the Z rotation data
			}
			
			m_registry.emplace<TransformComponent>(m_entities[i], loadedPosition, loadedRotation, loadedScale); // emplace the transform component on the entity using loaded data
			
			glm::vec4 loadedTint; // Vector4 for the loaded tint
			auto& tint = jsonData[i]["colour"]; // tint is the JSON data under "colour"

			if (tint.count("r") > 0) loadedTint.r = tint["r"].get<float>(); // Load the R value data
			if (tint.count("g") > 0) loadedTint.g = tint["g"].get<float>(); // Load the G value data
			if (tint.count("b") > 0) loadedTint.b = tint["b"].get<float>(); // Load the B value data
			if (tint.count("a") > 0) loadedTint.a = tint["a"].get<float>(); // Load the A value data

			m_registry.get<RenderComponent>(m_entities[i]).getMaterial()->setTint(loadedTint); // Emplace the render component using the tint

			auto& col = jsonData[i]["CRBTYPE"]; // col is the JSON data for the CRBTYPE
			int index = 0; // Index
			if (col.count("COLLIDER") > 0) // If col count for "Collider" is bigger than 0...
			{
				switch (col["COLLIDER"].get<uint32_t>()) // Switch case for the uint32_t value
				{
				case 0:
					addBoxCollider(m_entities[i], RigidBodyType::Static, glm::vec3(loadedScale.x / 2, loadedScale.y / 2, loadedScale.z / 2), index + 1); // Emplace collider which is static
					break;

				case 1:
					addBoxCollider(m_entities[i], RigidBodyType::Dynamic, glm::vec3(loadedScale.x / 2, loadedScale.y / 2, loadedScale.z / 2), index + 1); // Emplace collider which is dynamic
					break;

				case 2:
					addBoxCollider(m_entities[i], RigidBodyType::Kinematic, glm::vec3(loadedScale.x / 2, loadedScale.y / 2, loadedScale.z / 2), index + 1); // Emplace collider which is kinematic
					break;
				default:
					Logger::error("No Number Found!");
					break;
				}
			}

			auto& trig = jsonData[i]["TRIGTYPE"]; // col is the JSON data for the TRIGTYPE
			if (trig.count("COLLIDER") > 0) // If col count for "Collider" is bigger than 0...
			{
				switch (trig["COLLIDER"].get<uint32_t>()) // Switch case for the uint32_t value
				{
				case 0:
					addSphereTrigger(m_entities[i], RigidBodyType::Static, 0.5f, index + 1); // Emplace trigger which is static
					break;

				case 1:
					addSphereTrigger(m_entities[i], RigidBodyType::Dynamic, 0.5f, index + 1); // Emplace trigger which is dynamic
					break;

				case 2:
					addSphereTrigger(m_entities[i], RigidBodyType::Kinematic, 0.5f, index + 1); // Emplace trigger which is kinematic
					break;
				default:
					Logger::error("No Number Found!");
					break;
				}
			}
		}

		RendererCommon::clearCommand = renderCommands::getSetClearColourCommand(jsonData[jsonData.size() - 1]["bColour"]["r"].get<float>(), jsonData[jsonData.size() - 1]["bColour"]["g"].get<float>(),
			jsonData[jsonData.size() - 1]["bColour"]["b"].get<float>(), jsonData[jsonData.size() - 1]["bColour"]["a"].get<float>()); // Set background colour to JSON data

		//Parent Hierachy/////////////////////////////////////////
		m_registry.emplace<RelationshipComponent>(m_entities[0]);


	}

	void EnTTLayer::onRender()
	{
		glm::vec3 tmp = Camera3D->getPosition();
		lightUBO->uploadData("u_viewPos", glm::value_ptr(tmp));

		RendererCommon::actionCommand(RendererCommon::setDepthTestEnabled);
		RendererCommon::actionCommand(RendererCommon::clearColourAndDepth);

		Renderer3D::begin(m_swu);

		auto group = m_registry.group<TransformComponent, RenderComponent>();
		for (auto entity : group)
		{
			auto& transform = group.get<TransformComponent>(entity);
			auto& render = group.get<RenderComponent>(entity);

			Renderer3D::submit(render.geometry, render.material, transform.getTransform());
		}

		auto view = m_registry.view<BoxColliderComponent, RigidBodyComponent, TransformComponent>();
		for (auto entity : view)
		{
			//auto& col = view.get<BoxColliderComponent>(entity);
			auto& rb = view.get<RigidBodyComponent>(entity);
			auto& transform = view.get<TransformComponent>(entity);

			glm::mat4 t;
			rb.m_body->getTransform().getOpenGLMatrix(glm::value_ptr(t));

			glm::mat4 s;
			s = glm::scale(glm::mat4(1), transform.getScale());

			renderCommands::getSetWireFrame();
			//Renderer3D::submit(cubeVAO, pyramidMaterial, t * s);
		}

		auto view2 = m_registry.view<SphereColliderComponent, RigidBodyComponent, TransformComponent>();
		for (auto entity : view2)
		{
			//auto& col = view.get<SphereColliderComponent>(entity);
			auto& rb = view2.get<RigidBodyComponent>(entity);
			auto& transform = view2.get<TransformComponent>(entity);

			glm::mat4 t;
			rb.m_body->getTransform().getOpenGLMatrix(glm::value_ptr(t));

			glm::mat4 s;
			s = glm::scale(glm::mat4(1), transform.getScale());

			renderCommands::getSetWireFrame();

			//Renderer3D::submit(sphereVAO, pyramidMaterial, t * s);
		}

		Renderer3D::end();
	}

	void EnTTLayer::onUpdate(float timestep)
	{
		bool updateView = false;
		

		camera3D_UBO->uploadData("u_projection", glm::value_ptr(Camera3D->getCamera().projection)); //!< Upload Projection Data for active camera
		camera3D_UBO->uploadData("u_view", glm::value_ptr(Camera3D->getCamera().view)); //!< Upload View Data for active camera
		glm::vec3 tmp = Camera3D->getPosition();
		lightUBO->uploadData("u_viewPos", glm::value_ptr(tmp));
	}

	void EnTTLayer::addBoxCollider(entt::entity & entity, RigidBodyType RBtype, glm::vec3 halfExtents, uint32_t index)
	{
		glm::mat4& transform = m_registry.get <TransformComponent>(entity).getTransform();
		RigidBodyComponent rb = m_registry.emplace<RigidBodyComponent>(entity, RBtype, transform, index);
		m_registry.emplace<BoxColliderComponent>(entity, rb, halfExtents);
	}

	void EnTTLayer::addSphereCollider(entt::entity & entity, RigidBodyType type, float radius, uint32_t index)
	{
		glm::mat4& t = m_registry.get<TransformComponent>(entity).getTransform();
		RigidBodyComponent rb = m_registry.emplace<RigidBodyComponent>(entity, type, t, index);
		m_registry.emplace<SphereColliderComponent>(entity, rb, radius);//glm::vec3(1.f, 1.f, 1.f));
	}

	void EnTTLayer::addSphereTrigger(entt::entity & entity, RigidBodyType type, float radius, uint32_t index)
	{
		glm::mat4& t = m_registry.get<TransformComponent>(entity).getTransform();
		RigidBodyComponent rb = m_registry.emplace<RigidBodyComponent>(entity, type, t, index);
		m_registry.emplace<SphereTriggerComponent>(entity, rb, radius);//glm::vec3(1.f, 1.f, 1.f));
	}
