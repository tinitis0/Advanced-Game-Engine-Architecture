
#include "engine_pch.h"
#include "systems/physicsSystem.h"
#include "Platform/EnTT/Components/physics.h"
#include "Platform/EnTT/Components/transform.h"

void Engine::NGPhysicsSystem::updateTransforms()
{
	auto& registry = Application::getInstance().m_registry; //!< Get the registry
	auto view = registry.view<RigidBodyComponent, TransformComponent>(); //!< Get every entity with a rigidbody and transform component
	for (auto entity : view) //!< Loop through the entities
	{
		auto& rb = registry.get<RigidBodyComponent>(entity); //!< Get the rigidbody component
		auto& transform = registry.get<TransformComponent>(entity); //!< Get the transform component
		auto rbTransform = rb.m_body->getTransform(); //!< Get the rigidbody transform
		glm::vec3 t(rbTransform.getPosition().x, rbTransform.getPosition().y, rbTransform.getPosition().z); //!< Get the rigidbody position
		glm::quat r(rbTransform.getOrientation().w, rbTransform.getOrientation().x, rbTransform.getOrientation().y, rbTransform.getOrientation().z); //!< Get the rigidbody orientation
		transform.setTransform(t, r, transform.scale); //!< Set the transform component's transform to the rigidbody's transform
	}
}
