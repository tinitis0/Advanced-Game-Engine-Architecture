/*! \file EnTTLayer.h */
#pragma once

#include "Platform/Renderer/RendererCommon.h"
#include "Platform/Renderer/3D_Renderer.h"
#include "Platform/EnTT/Components/render.h"
#include "Platform/EnTT/Components/transform.h"
#include "Platform/EnTT/Components/keyController.h"
#include "Platform/EnTT/Components/cameras.h"
#include "Platform/EnTT/Components/relationship.h"
#include "Platform/EnTT/Components/label.h"
#include "Platform/EnTT/Components/physics.h"
#include "Camera/Camera.h"
#include "core/inputPoller.h"
#include "Rendering/Shader.h"
#include "core/layer.h"
#include "Rendering/frameBuffer.h"

#include "Include.h"
#include <entt/entt.hpp>
#include "json.hpp"
#include <fstream>

using namespace Engine;
class imGUILayer;
	class EnTTLayer : public Layer
	{
		friend class imGUILayer;
	public:
		EnTTLayer(const char* name);
		void onRender() override;
		void onUpdate(float timestep);
		void loadEntities(nlohmann::json jsonData);

		std::shared_ptr<FreeEuler3DCamera> getCamera() { return Camera3D; }

		void addBoxCollider(entt::entity& entity, RigidBodyType type, glm::vec3 halfExtents, uint32_t index);
		void addSphereCollider(entt::entity& entity, RigidBodyType type, float radius, uint32_t index);
		void addSphereTrigger(entt::entity & entity, RigidBodyType type, float radius, uint32_t index);

	private:
		SceneWideUniforms m_swu;

		std::shared_ptr<Material> pyramidMaterial;//!< Pyramid Shape Material
		std::shared_ptr<Material> letterCubeMat;
		std::shared_ptr<Material> numberCubeMat;
		std::shared_ptr<Material> letterAndNumberMat;

		std::shared_ptr<Shader> TPShader;

		std::shared_ptr<Textures> letterTexture;
		std::shared_ptr<Textures> numberTexture;
		std::shared_ptr<Textures> plainWhiteTexture;

		std::shared_ptr<vertexArray> cubeVAO; //!< Cube Vertex array object is an OpenGL vertex array
		std::shared_ptr<vertexArray> pyramidVAO; //!< Pyramid Vertex array object is an OpenGL vertex array
		
		std::shared_ptr<ResourceManager> RM;

		entt::registry& m_registry;
		std::vector<entt::entity>& m_entities;

		entt::entity m_currentCamera;

		static std::shared_ptr<FrameBuffer> FB;

		std::shared_ptr <FreeEuler3DCamera> Camera3D; //!< Euler Camera
		std::shared_ptr <FollowCamera3D> Follow3D; //!< Follow Camera

		//FreeEuler3DCamera Camera3D;
		//FollowCamera3D Follow3D;

		CameraController* activeCam;

		std::shared_ptr<UniformBuffer> camera3D_UBO; //!< Defining the UniformBuffer as cameraUBO
		std::shared_ptr<UniformBuffer> lightUBO;

		std::shared_ptr<FrameBuffer> m_sceneFBO;
		std::shared_ptr<FrameBuffer> m_defaultFBO;


		//Layer layer;
	};
