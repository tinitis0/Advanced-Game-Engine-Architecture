/* \file physicsSystem.h */

#pragma once

#include <systems/system.h>
#include <reactphysics3d/reactphysics3d.h>
#include "systems/Logger.h"
#include <reactphysics3d/collision/OverlapCallback.h>
//#include <reactphysics3d/engine/EventListener.h>
#include "core/resources.h"

namespace Engine
{
	/*!
	\class WorldEventListener
	The event listener for the world. Handles collisions
	*/

	class WorldEventListener : public reactphysics3d::EventListener
	{
	public:
		std::shared_ptr<ResourceManager> rManager; //!< Pointer to the resource manager

		virtual void onContact(const CollisionCallback::CallbackData& callbackData) override //!< Function called on contact
		{
			for (int i = 0; i < callbackData.getNbContactPairs(); i++) //!< Goes through each contact pair
			{
				CollisionCallback::ContactPair contPair = callbackData.getContactPair(i); //!< Gets the pair's data

				for (int j = 0; j < contPair.getNbContactPoints(); j++) //!< Goes through the contact data for the contact point
				{
					CollisionCallback::ContactPoint contPoint = contPair.getContactPoint(j); //!< Gets the contact point

					reactphysics3d::Vector3 worldPoint = contPair.getCollider1()->getLocalToWorldTransform() * contPoint.getLocalPointOnCollider1(); //!< Gets the contact point in world space
				}
			}
		}

		virtual void onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData) override //!< called when an object hits a trigger
		{
			for (int i = 0; i < callbackData.getNbOverlappingPairs(); i++) //!< Gets the overlapping pairs
			{
				rp3d::OverlapCallback::OverlapPair contPair = callbackData.getOverlappingPair(i); //!< Assign the overlapping pairs to a variable

				uint32_t index1 = reinterpret_cast<uint32_t>(contPair.getBody1()->getUserData()); //!< get the first bodies data
				uint32_t index2 = reinterpret_cast<uint32_t>(contPair.getBody2()->getUserData()); //!< Get the second bodies data
				//Application::getInstance().m_registry to get the registry.
				if (index1 == 1  && index2 == 9 || index2 == 1 && index1 == 9) //!< If the ball hits the first hole
				{
					Logger::info("Hole 1 Hit!");//!< Log hole 1 is hit
					rManager->setLevel(2);		//!< Set the current level number
					rManager->nextLevel = true;	//!< Set nextlevel to true so EnTT will change the level
					rManager->maxStrokes = 3;	//!< Change the maximum strokes to 3
				}
				else if (index1 == 1 && index2 == 18 || index1 == 18 && index2 == 1) //!< If the ball hits the second hole
				{
					Logger::info("Hole 2 Hit!");//!< Log hole 2 is hit
					rManager->setLevel(3);		//!< Set the current level number
					rManager->nextLevel = true; //!< Set nextlevel to true so EnTT will change the level
					rManager->maxStrokes = 3;	//!< Change the maximum strokes to 3
				}
				else if (index1 == 1 && index2 == 25 || index1 == 25 && index2 == 1) //!< If the ball hits the final hole
				{
					Logger::info("Hole 3 Hit! GAME OVER!"); //!< Log the game is over
					rManager->finished = true; //!< Set finished to true in the resource manager
				}
				else if (index1 == 10 && index2 == 1 || index2 == 10 && index1 == 1) //!< If the ball hits the hazard zone by going off of the map
				{
					Logger::error("Ball Fell Off!"); //!< Log the ball has fallen off
					rManager->reset = true; //!< Set reset to true so EnTT resets the ball
				}

			}
		}
	};

	/*!
	\class PhysicsSystem
	The system that handles physics, including the physics world and the event listener
	*/

	class PhysicsSystem : public System
	{
	public:
		WorldEventListener listener; //!< The listener for collisions
		void start(SystemSignal init = SystemSignal::None, ...) override //!< Start the physics system
		{
			m_world = m_3DPhysCommon.createPhysicsWorld(); //!< create the physics world
			m_world->setEventListener(&listener); //!< Set the event listener
		}

		void stop(SystemSignal close = SystemSignal::None, ...) override //!< Stop the system
		{
			m_3DPhysCommon.destroyPhysicsWorld(m_world); //!< destroy the physics world
		}

		rp3d::PhysicsWorld* m_world; //!< Pointer to the physics world
		rp3d::PhysicsCommon m_3DPhysCommon; //!< Physics common
	};
}