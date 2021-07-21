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

using namespace Engine;

	/*!
	\class EnTTLayer
	The EnTT layer is the basis for the 3D world.
	The EnTT layer contains all entities and their components.
	*/
	class EnTTLayer : public Layer
	{
	friend class ImGuiLayer;
	public:
		EnTTLayer(const char* name); //!< Constructor for the EnTT layer
		void onRender() override; //!< On render override
		void onUpdate(float timestep); //!< On update, called every frame
	 
		void addBoxCollider(entt::entity& entity, RigidBodyType type, glm::vec3 halfExtents, uint32_t index); //!< Function for adding react physics 3d box colliders
		void addSphereCollider(entt::entity& entity, RigidBodyType type, float radius, uint32_t index); //!< Function for adding RP3D sphere colliders
		void addSphereTrigger(entt::entity & entity, RigidBodyType type, float radius, uint32_t index); //!< Function for adding RP3D sphere triggers.
		//There is code for a box trigger function, however it is not implemented.

		inline int getStrokes() { return strokes; } //!< Getter for the stroked
		inline float getForce() { return force; } //!< Getter for the force

		void SetBallToStartPos(); //!< Function for setting the ball's position, whether that is to the start of the level or the next level.
	private:

		std::shared_ptr<vertexArray> cubeVAO; //!< Cube Vertex array object is an OpenGL vertex array
		std::shared_ptr<vertexArray> sphereVAO; //!< SphereVAO, also saved in the resource manager
		std::shared_ptr<Shader> TPShader; //!< Textured phong shader
		std::shared_ptr<Textures> letterTexture; //!< Texture for the letter cube. No longer used.
		std::shared_ptr<Textures> numberTexture; //!< Texture for the number cube. No longer used.
		std::shared_ptr<Textures> plainWhiteTexture; //!< Plain white texture. Easy to apply tints to, as it is plain white

		std::shared_ptr<ResourceManager> rManager; //!< Pointer to the resource manager

		SceneWideUniforms m_swu; //!< Scene wide uniforms

		bool Shooting = false; //!< Boolean for if the player is shooting
		bool forceChange; //!< Boolean for if the force should be increasing or decreasing
		float force = 0; //!< Float for the force value
		int strokes = 0; //!< integer for the taken strokes

		std::shared_ptr<Material> pyramidMat; //!< Pyramid's material
		std::shared_ptr<Material> letterCubeMat; //!< Letter cube's material
		std::shared_ptr<Material> numberCubeMat; //!< Number cube's material
		std::shared_ptr<Material> letterAndNumberMat; //!< Material with both the letter and number textures used as a texture atlas

		

		//std::shared_ptr<vertexArray> cube, pyramid;

		entt::registry& m_registry; //!< Registry filled with the entities
		std::vector<entt::entity>& m_entities; //!< Entity stack

		//entt::entity m_currentCamera;

		std::shared_ptr <FreeEuler3DCamera> Camera3D; //!< Euler Camera
		std::shared_ptr <FollowCamera3D> Follow3D; //!< Follow Camera

		//FreeEuler3DCamera Camera3D;
		//FollowCamera3D Follow3D;

		CameraController* activeCam; //!< Active camera

		int cam = 1; //!< Camera mode variable

		std::shared_ptr<UniformBuffer> camera3D_UBO; //!< Defining the UniformBuffer as cameraUBO
		std::shared_ptr<UniformBuffer> lightUBO; //!< the UBO for the light

		std::shared_ptr<FrameBuffer> textureTarget; //!< FBO texture
		std::shared_ptr<FrameBuffer> defaultFBO; //!< Default frame buffer

		//glm::vec3 m_rotation = { 0.f, 0.f, 0.f }; // assimp controls dont delete
		//float m_scale = 1.f; // assimp controls dont delete

		//Layer layer;
	};
