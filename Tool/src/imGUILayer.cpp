#include "imGUILayer.h"

 entt::entity imGUILayer::selectedEntity = entt::null;

imGUILayer::imGUILayer(const char * name,EnTTLayer * enttLayer) : 
	Layer(name), 
	m_enttLayer(*enttLayer),
	m_registry(Application::getInstance().m_registry),
	m_entities(Application::getInstance().m_entities)
{
	auto& window = Application::getInstance().getWindow();

	window->setSize({1600, 980});

	FrameBufferLayout FBlayout = { {AttachmentType::Colour, true}, {AttachmentType::Depth, false} };
	m_sceneFBO.reset(FrameBuffer::create({ window->getWidth(), window->getHeight() }, FBlayout));

	m_defaultFBO.reset(FrameBuffer::createDefault());
}

void imGUILayer::onRender()
{
	m_defaultFBO->use();

	ImGuiHelper::begin();

	ImGui::Begin("Render Output");
	uint32_t textureID = m_sceneFBO->getTarget(0)->getRenderID();
	ImGui::Image((void*)textureID, ImVec2{ 920, 840 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	if (ImGui::IsWindowHovered()) m_mouseOverScene = true;
	else m_mouseOverScene = false;
	ImGui::End();
	
	ImGui::Begin("Properties");

	ImGui::TextWrapped("Load & Save Level:");
	ImGui::TextWrapped("File:");
	ImGui::SameLine();
	if (ImGui::Button("Save")) saveJSONfile("./assets/json/level.json");

	ImGui::TextWrapped("Add Geometry:"); // Add geometry section

	if (ImGui::CollapsingHeader("3D Object")) // Collapsing header for 3D Geometry
	{
		if (ImGui::Button("Cube")) // Add cube button...
		{
			entt::entity entity = m_registry.create(); // Create new registry entry
			m_entities.push_back(entity); // Push back the entity
			
			m_registry.emplace<LabelComponent>(entity, "New Cube"); // Give it a label
			m_registry.emplace<RenderComponent>(entity, m_enttLayer.cubeVAO, m_enttLayer.TPShader, m_enttLayer.plainWhiteTexture, 1); // Render
			m_registry.emplace<TransformComponent>(entity, glm::vec3(0.f, 0.f, -10.f), glm::vec3(0.f), glm::vec3(1.f)); // Set the default transform on render
			addBoxCollider(entity, RigidBodyType::Static, glm::vec3(0.5f), index); // Give it a collider
			index += 1; // Increase index by 1
		}

		if (ImGui::Button("Pyramid")) // Add pyramid button...
		{
			entt::entity entity = m_registry.create(); // Create new registry entry
			m_entities.push_back(entity); // Push back the entity

			m_registry.emplace<LabelComponent>(entity, "New Pyramid"); // Give it a label
			m_registry.emplace<RenderComponent>(entity, m_enttLayer.pyramidVAO, m_enttLayer.TPShader, m_enttLayer.plainWhiteTexture, 2); // Render
			m_registry.emplace<TransformComponent>(entity, glm::vec3(0.f, 0.f, -10.f), glm::vec3(0.f), glm::vec3(1.f)); // Set the default transform on render
		}

		if (ImGui::Button("Hole")) // Add hole button...
		{
			entt::entity entity = m_registry.create(); // Create new registry entry
			m_entities.push_back(entity); // Push back the entity

			m_registry.emplace<LabelComponent>(entity, "New Hole"); // Give it a label
			m_registry.emplace<RenderComponent>(entity, m_enttLayer.cubeVAO, m_enttLayer.TPShader, m_enttLayer.plainWhiteTexture, 1); // Render
			m_registry.emplace<TransformComponent>(entity, glm::vec3(0.f, 0.f, -10.f), glm::vec3(0.f), glm::vec3(0.25f)); // Set the default transform on render
			addSphereTrigger(entity, RigidBodyType::Static, 0.5f, index); // Give it a trigger
		}

	}

	ImGui::TextWrapped("Background Colour:"); // Text for section background colour area...

	if (ImGui::CollapsingHeader("Background Colour")) // Header for "background colour"
	{
		ImGui::ColorPicker4("Colour", backCol); // Colour picker
		auto i = renderCommands::getSetClearColourCommand(backCol[0], backCol[1], backCol[2], backCol[3]); // Set the colour selected
		RendererCommon::actionCommand(i); // Complete action
	}

	ImGui::End(); // End Section

	ImGui::Begin("Inspector"); // Begin new panel for Inspector  
	
	ImGui::TextWrapped("GameObject Name:"); // Text for object name

	ImGui::SameLine();

	if (selectedEntity != entt::null) // if there is a selected entity
	{
		auto& LabelComp = m_registry.get<LabelComponent>(selectedEntity); // Get label of entity
	
		char buf[128]; // Buffer size
		strcpy(buf, LabelComp.label.c_str());
		ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() - 65); // Item width
		if (ImGui::InputText(std::string("###NameTop").c_str(), buf, IM_ARRAYSIZE(buf))) LabelComp.label = std::string(buf).c_str(); // Input ext
		ImGui::PopItemWidth();
	}
	else
	{
		char buf[128]; // Buffer size
		strcpy(buf, ""); // Empty label
		ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() - 65);
		if (ImGui::InputText(std::string("###NameTop").c_str(), buf, IM_ARRAYSIZE(buf)));
		ImGui::PopItemWidth();
	}

	ImGui::NewLine(); // New line

	if (ImGui::CollapsingHeader("Transform")) // Collapsing header for the object transform
	{
		if (selectedEntity != entt::null) // If selected entity is not null...
		{
			// get the transform compoenent for selected entity
			auto& t = m_registry.get<TransformComponent>(selectedEntity);

			// Boxes for the X, Y, Z Transform for entity
			ImGui::DragFloat3("Transform", &t.getPosition().x, 0.1f, -180.f, 180.f, "%.2f");
			 
			// Boxes for the X, Y, Z Rotation for entity
			ImGui::DragFloat3("Rotation", &t.getRotationEuler().x, 1.f, 0.f, 360.f, "%.2f");
			t.setRotationDegrees(t.getRotationEuler());

			// Boxes for the X, Y, Z Scale for entity
			ImGui::DragFloat3("Scale", &t.getScale().x, 0.1f, 0.f, 0.f, "%.2f");

			t.updateTransform(); // Update the transform

			if (m_registry.has<BoxColliderComponent>(selectedEntity)) // If entity has a box collider...
			{
				auto& c = m_registry.get<RigidBodyComponent>(selectedEntity); // Get box collider component
				rp3d::Vector3 pos = { t.getPosition().x, t.getPosition().y, t.getPosition().z }; // Get the position of entity
				rp3d::Quaternion orient = { t.getRotationQuat().x, t.getRotationQuat().y, t.getRotationQuat().z, t.getRotationQuat().w }; // Get rotation of entity
				rp3d::Transform transform = rp3d::Transform(pos, orient); // Set the transform
				
				c.m_body->setTransform(transform); // Set collider transofrm to be same as entity
			}
		}
	}

	if (ImGui::CollapsingHeader("Colour")) // Collapsing header for entity colour...
	{
		if (selectedEntity != entt::null) // If selected entity is not null...
		{
			auto t = m_registry.get<RenderComponent>(selectedEntity); // Get the render component

			float col[4] = { t.getMaterial()->getTint().r, t.getMaterial()->getTint().g, t.getMaterial()->getTint().b, t.getMaterial()->getTint().a }; // Get materials RGBA values
			ImGui::ColorPicker4("Colour", col); // Create a colour picker using these values
			t.getMaterial()->setTint(glm::vec4(col[0], col[1], col[2], col[3])); // Set the colour set in colour picker
		}
	}

	if (ImGui::Button("Remove"))
	{
		if (selectedEntity != entt::null)
		{
			// write ImGUI widgets
			m_registry.destroy(selectedEntity);
			selectedEntity = entt::null;
		}
	}

	ImGui::End(); // End inspector section

	ImGui::Begin("Hierarchy"); // Begin hierarchy section

	auto labelView = m_registry.view<LabelComponent>(); // View the label component

	for (auto entity : labelView) // Entity label
	{
		auto LabelComp = m_registry.get<LabelComponent>(entity); // Get the label component

		if (ImGui::Button(LabelComp.label.c_str())) // Labels are object selection buttons
		{
			selectedEntity = entity; // Selected entity becomes the entity chosen
		}
	}

	ImGui::End(); // End hierarchy section

	ImGuiHelper::end(); // End imGUI

	m_sceneFBO->use(); // Set the FrameBuffer
}

void imGUILayer::onUpdate(float timestep)
{
	if (m_mouseOverScene) m_enttLayer.getCamera()->onUpdate(timestep); // If mouse is not over screen, do not update camera
}

void imGUILayer::addBoxCollider(entt::entity & entity, RigidBodyType RBtype, glm::vec3 halfExtents, uint32_t index)
{
	glm::mat4& transform = m_registry.get <TransformComponent>(entity).getTransform();
	RigidBodyComponent rb = m_registry.emplace<RigidBodyComponent>(entity, RBtype, transform, index);
	m_registry.emplace<BoxColliderComponent>(entity, rb, halfExtents);
}

void imGUILayer::addSphereCollider(entt::entity & entity, RigidBodyType type, float radius, uint32_t index)
{
	glm::mat4& t = m_registry.get<TransformComponent>(entity).getTransform();
	RigidBodyComponent rb = m_registry.emplace<RigidBodyComponent>(entity, type, t, index);
	m_registry.emplace<SphereColliderComponent>(entity, rb, radius);//glm::vec3(1.f, 1.f, 1.f));
}

void imGUILayer::addSphereTrigger(entt::entity & entity, RigidBodyType type, float radius, uint32_t index)
{
	glm::mat4& t = m_registry.get<TransformComponent>(entity).getTransform();
	RigidBodyComponent rb = m_registry.emplace<RigidBodyComponent>(entity, type, t, index);
	m_registry.emplace<SphereTriggerComponent>(entity, rb, radius);//glm::vec3(1.f, 1.f, 1.f));
}


bool imGUILayer::saveJSONfile(std::string filePath) // Save to JSON file
{
	nlohmann::json jsonData;

	// JSON Data...

	std::ofstream handle(filePath); // Handle is the filepath chosen

	int index = 0; // Index

	for (uint32_t i = 0; i < m_entities.size(); i++) // For all entities in m_entities starting from 0...
	{
		index++; // Increase index

		if (m_registry.has<LabelComponent>(m_entities[i])) // If entity has a label component...
		{
			LabelComponent& label = m_registry.get<LabelComponent>(m_entities[i]); // Get the label
			jsonData[i]["label"] = label.label; // Set the label in JSON data
		}

		if (m_registry.has<TransformComponent>(m_entities[i])) // If entity has a tranform component...
		{
			TransformComponent& tc = m_registry.get<TransformComponent>(m_entities[i]); // Get the transform component
			jsonData[i]["transform"]["pos"]["x"] = tc.getPosition().x; // Add X transform to JSON data
			jsonData[i]["transform"]["pos"]["y"] = tc.getPosition().y; // Add Y transform to JSON data
			jsonData[i]["transform"]["pos"]["z"] = tc.getPosition().z; // Add Z transform to JSON data
			jsonData[i]["transform"]["scale"]["x"] = tc.getScale().x; // Add X scale to JSON data
			jsonData[i]["transform"]["scale"]["y"] = tc.getScale().y; // Add Y scale to JSON data
			jsonData[i]["transform"]["scale"]["z"] = tc.getScale().z; // Add Z scale to JSON data
			jsonData[i]["transform"]["rotation"]["x"] = tc.getRotationEuler().x; // Add X rotation to JSON data
			jsonData[i]["transform"]["rotation"]["y"] = tc.getRotationEuler().y; // Add Y rotation to JSON data
			jsonData[i]["transform"]["rotation"]["z"] = tc.getRotationEuler().z; // Add Z rotation to JSON data
		}

		if (m_registry.has<RenderComponent>(m_entities[i])) // If entity has a render component...
		{
			RenderComponent& rc = m_registry.get<RenderComponent>(m_entities[i]); // Get render component
			jsonData[i]["colour"]["r"] = rc.material->getTint().r; // Save tint R value
			jsonData[i]["colour"]["g"] = rc.material->getTint().g; // Save tint G value
			jsonData[i]["colour"]["b"] = rc.material->getTint().b; // Save tint B value
			jsonData[i]["colour"]["a"] = rc.material->getTint().a; // Save tint A value
		}

		if (m_registry.has<RenderComponent>(m_entities[i])) // If entity has a render component...
		{
			RenderComponent& rc = m_registry.get<RenderComponent>(m_entities[i]); // Get the render component
			switch (rc.getType()) // Switch for the VAO type
			{
			case 0:
				jsonData[i]["render"]["VAO"] = 0; // Save Sphere VAO type
				break;
			case 1:
				jsonData[i]["render"]["VAO"] = 1; // Save Cube VAO type
				break;
			
			case 2:
				jsonData[i]["render"]["VAO"] = 2; // Save Pyramid VAO type
				break;
			default:
				break;
			}
		}

		if (m_registry.has<BoxColliderComponent>(m_entities[i])) // If entity has a box collider component...
		{
			BoxColliderComponent& boxC = m_registry.get<BoxColliderComponent>(m_entities[i]); // Get the box collider component
			switch (m_registry.get<RigidBodyComponent>(m_entities[i]).m_body->getType()) // Switch for the RigidBody type
			{
			case rp3d::BodyType::DYNAMIC:
				jsonData[i]["CRBTYPE"]["COLLIDER"] = 1; // Save DYNAMIC to value 1
				break;
			case rp3d::BodyType::STATIC:
				jsonData[i]["CRBTYPE"]["COLLIDER"] = 0; // Save STATIC to value 0
				break;
			case rp3d::BodyType::KINEMATIC:
				jsonData[i]["CRBTYPE"]["COLLIDER"] = 2; // Save KINEMATIC to value 2
				break;
			default:
				break;
			}
		}

		if (m_registry.has<SphereTriggerComponent>(m_entities[i])) // If entity has a Sphere trigger component...
		{
			SphereTriggerComponent& boxC = m_registry.get<SphereTriggerComponent>(m_entities[i]); // Get the sphere trigger component
			switch (m_registry.get<RigidBodyComponent>(m_entities[i]).m_body->getType()) // Switch for the RigidBody type
			{
			case rp3d::BodyType::DYNAMIC:
				jsonData[i]["TRIGTYPE"]["COLLIDER"] = 1; // Save DYNAMIC to value 1
				break;
			case rp3d::BodyType::STATIC:
				jsonData[i]["TRIGTYPE"]["COLLIDER"] = 0; // Save STATIC to value 0
				break;
			case rp3d::BodyType::KINEMATIC:
				jsonData[i]["TRIGTYPE"]["COLLIDER"] = 2; // Save KINEMATIC to value 2
				break;
			default:
				break;
			}
		}

		if (m_registry.has<SphereColliderComponent>(m_entities[i])) // If entity has a Sphere collider component...
		{
			SphereColliderComponent& boxC = m_registry.get<SphereColliderComponent>(m_entities[i]); // Get the sphere collider component
			switch (m_registry.get<RigidBodyComponent>(m_entities[i]).m_body->getType()) // Switch for the RigidBody type
			{
			case rp3d::BodyType::DYNAMIC:
				jsonData[i]["SRBTYPE"]["DYNAMIC"] = 1; // Save DYNAMIC to value 1
				break;
			case rp3d::BodyType::STATIC:
				jsonData[i]["SRBTYPE"]["STATIC"] = 0; // Save STATIC to value 0
				break;
			case rp3d::BodyType::KINEMATIC:
				jsonData[i]["SRBTYPE"]["KINEMATIC"] = 2; // Save KINEMATIC to value 2
				break;
			default:
				break;
			}
		}
	}
	
	// Background Colour
	index = index + 1; // Increase index
	jsonData[index]["bColour"]["r"] = backCol[0]; // Save background colour R value
	jsonData[index]["bColour"]["g"] = backCol[1]; // Save background colour G value
	jsonData[index]["bColour"]["b"] = backCol[2]; // Save background colour B value
	jsonData[index]["bColour"]["a"] = backCol[3]; // Save background colour A value

	handle << jsonData; // Handle is the JSON data
	handle.close(); // Close the handle

	Logger::info("Level Data Saved."); // Log that it has saved
	return true;
}

nlohmann::json imGUILayer::loadJSONfile(std::string filePath)
{
	nlohmann::json jsonData;
	std::ifstream handle(filePath); // Handle is the file path

	if (handle.is_open()) // If handle is open
	{
		handle >> jsonData; // Handle is the JSON data
		
		// Data is loaded in EnTTLayer on load

		handle.close(); // Close handle
		Logger::info("Level Data Loaded."); // Log data has loaded
	}
	else
	{
		Logger::error("Could Not Open JSON File."); // Log if not JSON file is found
	}

	return jsonData; // Return the JSON data
}
