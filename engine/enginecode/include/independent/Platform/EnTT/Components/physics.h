#pragma once

#include <glm/gtc/type_ptr.hpp>
#include "engine.h"


namespace Engine
{
	enum class RigidBodyType { Static, Kinematic, Dynamic };
	class RigidBodyComponent
	{
	public:
		RigidBodyComponent() //!< Plain constructor
		{
			rp3d::PhysicsWorld* world = Application::getInstance().getWorld(); //!< Get the physics world
			rp3d::Vector3 position(0.0, 0.0, 0.0); //!< Default position
			rp3d::Quaternion orientation = rp3d::Quaternion::identity(); //!< Default quaternion
			rp3d::Transform transform(position, orientation); //!< Make a transform with the previous position and quaternion
		
			m_body = world->createRigidBody(transform); //!< Create a rigidbody with the previous transform
			m_body->setType(rp3d::BodyType::DYNAMIC); //!< Set the rigidbody type to dynamic
		}

		RigidBodyComponent(RigidBodyType type, uint32_t index) //Constructor takes a type and an index
		{
			rp3d::PhysicsWorld* world = Application::getInstance().getWorld(); //!< Get the world
			rp3d::Vector3 position(0.0, 0.0, 0.0); //!< Default position
			rp3d::Quaternion orientation = rp3d::Quaternion::identity(); //!< Default quaternion
			rp3d::Transform transform(position, orientation); //!< Make a transform with the previous position and quaternion

			m_body = world->createRigidBody(transform); //!< Create a rigidbody with the transform
			switch (type) //!< Switch through the type
			{
			case RigidBodyType::Static:
				m_body->setType(rp3d::BodyType::STATIC); //!< If it should be static, make it static
				break;
			case RigidBodyType::Dynamic:
				m_body->setType(rp3d::BodyType::DYNAMIC); //!< If it should be dynamic, make it dynamic
				break;
			case RigidBodyType::Kinematic:
				m_body->setType(rp3d::BodyType::KINEMATIC); //!< If it should be kinematic, make it kinematic
				break;
			default:
				m_body->setType(rp3d::BodyType::DYNAMIC); //Default isnt necessary here, but for errortrapping, cant hurt.
				break;
			}

			m_body->setUserData(reinterpret_cast<void*>(index)); //!< Set the user data to be the index as a void pointer
		}

		RigidBodyComponent(RigidBodyType type, glm::mat4& transform, uint32_t index)
		{
			rp3d::PhysicsWorld* world = Application::getInstance().getWorld();

			rp3d::Transform rpTransform; //!< Predefine the transform
			rpTransform.setFromOpenGL(glm::value_ptr(transform)); //!< Set the transform using an opengl transform

			rp3d::Quaternion quat = rpTransform.getOrientation(); //!< Set the orientation using the previously created transform
			quat.normalize(); //!< Normalise the quaternion
			rpTransform.setOrientation(quat); //!< Set the transform's orientation to the quaternion

			m_body = world->createRigidBody(rpTransform); //!< Create a rigidbody with the transform
			switch (type) //!< Switch through the type
			{
			case RigidBodyType::Static:
				m_body->setType(rp3d::BodyType::STATIC); //!< If it should be static, make it static
				break;
			case RigidBodyType::Dynamic:
				m_body->setType(rp3d::BodyType::DYNAMIC);  //!< If it should be dynamic, make it dynamic
				break;
			case RigidBodyType::Kinematic:
				m_body->setType(rp3d::BodyType::KINEMATIC); //!< If it should be kinematic, make it kinematic
				break;
			default:
				m_body->setType(rp3d::BodyType::DYNAMIC); //Default isnt necessary here, but for errortrapping, cant hurt.
				break;
			}
			m_body->setUserData(reinterpret_cast<void*>(index)); //!< Set the user data to be the index as a void pointer
		}

		rp3d::RigidBody* m_body; //!< Store the body


	};

	class BoxColliderComponent
	{ 
	public:
		BoxColliderComponent(RigidBodyComponent& bodyComp, glm::vec3& halfExtents)
		{
			auto& physCommon = Application::getInstance().getPhysicsCommon(); //!< Get the physics common
			rp3d::PhysicsWorld* world = Application::getInstance().getWorld(); //!< Get the physics world
			
			shape = physCommon.createBoxShape(rp3d::Vector3(halfExtents.x, halfExtents.y, halfExtents.z)); //!< Create the box for the collider

			rp3d::Transform transform = rp3d::Transform::identity(); //!< Create a transform

			collider = bodyComp.m_body->addCollider(shape, transform); //!< make the collider using the shape and transform
			
		}

		//Raw pointers as memory is handled by reactPhysics3D
		rp3d::BoxShape* shape; //!< Store the shape
		rp3d::Collider* collider = nullptr; //!< Default the stored collider to be a nullptr
	};

	class BoxTriggerComponent : public BoxColliderComponent //!< Code to add box triggers easily. Never implemented.
	{
	public:
		BoxTriggerComponent(RigidBodyComponent& bodyComp, glm::vec3& halfExtents) : BoxColliderComponent(bodyComp, halfExtents) //Constructor is the same as a boxcollider component
		{
			collider->setIsTrigger(true); //!< makes the collider a trigger
		}
	};

	class SphereColliderComponent
	{
	public:
		SphereColliderComponent(RigidBodyComponent& bodyComp, float radius)
		{
			auto& physCommon = Application::getInstance().getPhysicsCommon(); //!< Get the physics common
			rp3d::PhysicsWorld* world = Application::getInstance().getWorld(); //!< Get the physics world

			//shape = physCommon.createBoxShape(rp3d::Vector3(halfExtents.x, halfExtents.y, halfExtents.z));
			shape = physCommon.createSphereShape(radius); //!< Create a sphere with the radius

			rp3d::Transform transform = rp3d::Transform::identity(); //!< Create a transform

			collider = bodyComp.m_body->addCollider(shape, transform); //!< Make the collider with the shape and the transform
		}

		rp3d::SphereShape* shape; //Raw pointers as memory is handled by reactPhysics3D
		rp3d::Collider* collider = nullptr; //!< Store the collider
	};

	class SphereTriggerComponent : public SphereColliderComponent
	{
	public:
		SphereTriggerComponent(RigidBodyComponent& bodyComp, float radius) : SphereColliderComponent(bodyComp, radius) //!< Same as the sphere collider constructor inputs, and calls sphere collider component
		{
			collider->setIsTrigger(true); //!< Set the collider as a trigger
		}
	};

	class CapsuleColliderComponent
	{
	public:
		CapsuleColliderComponent(RigidBodyComponent& bodyComp, float radius, float height) //!< Capsule collider takes a rigidbody component, a radius and a height
		{
			auto& physCommon = Application::getInstance().getPhysicsCommon(); //!< Get the physics common
			rp3d::PhysicsWorld* world = Application::getInstance().getWorld(); //!< Get the physics world

			shape = physCommon.createCapsuleShape(radius, height); //!< Create a capsule shape using the radius and height

			rp3d::Transform transform = rp3d::Transform::identity(); //!< Create a transform

			collider = bodyComp.m_body->addCollider(shape, transform); //!< Create the collider with the shape and the transform
		}

		rp3d::CapsuleShape* shape; //Raw pointers as memory is handled by reactPhysics3D
		rp3d::Collider* collider = nullptr; //!< Store the collider
	};

	//class ConvexColliderComponent (NOT INCLUDED. ASSIMP WAS NEVER PROPERLY FINISHED, SO WAS NOT VERY NECESSARY.)
	//{
	//public:
	//	ConvexColliderComponent(RigidBodyComponent& bodyComp, float radius, float height)
	//	{
	//		auto& physCommon = Application::getInstance().getPhysicsCommon();
	//		rp3d::PhysicsWorld* world = Application::getInstance().getWorld();
	//
	//		shape = physCommon.createConvexMeshShape()
	//
	//		rp3d::Transform transform = rp3d::Transform::identity();
	//
	//		collider = bodyComp.m_body->addCollider(shape, transform);
	//	}
	//
	//	rp3d::CapsuleShape* shape; //Raw pointers as memory is handled by reactPhysics3D
	//	rp3d::Collider* collider = nullptr;
	//};

	namespace NGPhysicsSystem
	{
		void updateTransforms(); //!< Update the transforms using RP3D
	}
}