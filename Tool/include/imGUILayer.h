#pragma once

#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/application.h"
#include "Platform/GLFW/ImGuiHelper.h"
#include "json.hpp"
#include <fstream>
#include "EnTTLayer.h"

using namespace Engine;

class imGUILayer : public Layer
{
public:
	imGUILayer(const char * name, EnTTLayer * enttLayer);
	void onRender() override;
	void onUpdate(float timestep) override;
	void onKeyPressed(KeyPressed & e) override {};
	void onResize(WindowResizeEvent & e) override {};

	static nlohmann::json loadJSONfile(std::string filePath);
	bool saveJSONfile(std::string filePath);

	void addBoxCollider(entt::entity& entity, RigidBodyType type, glm::vec3 halfExtents, uint32_t index);
	void addSphereCollider(entt::entity& entity, RigidBodyType type, float radius, uint32_t index);
	void addSphereTrigger(entt::entity & entity, RigidBodyType type, float radius, uint32_t index);
private:
	std::shared_ptr<FrameBuffer> m_sceneFBO;
	std::shared_ptr<FrameBuffer> m_defaultFBO;
	entt::registry& m_registry;
	std::vector<entt::entity>& m_entities;
	EnTTLayer& m_enttLayer;
	float index;
	static entt::entity selectedEntity;
	float backCol[4] = {1.f, 1.f, 1.f, 1.f};
	bool m_mouseOverScene = true;
};