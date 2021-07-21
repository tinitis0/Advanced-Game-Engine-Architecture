/* \file relationship.cpp */

#include "engine_pch.h"
#include "Platform/EnTT/Components/relationship.h"
#include "Platform/EnTT/Components/transform.h"
#include "core/application.h"

namespace Engine
{
	namespace Hierachy
	{
		void setChild(entt::entity parentEntity, entt::entity childEntity)
		{
			entt::registry& registry = Application::getInstance().m_registry; //!< get the registry

			auto& parentComponent = registry.get<RelationshipComponent>(parentEntity); //!< Get the parent's relationship component
			auto& childComponent = registry.get<RelationshipComponent>(childEntity); //!< Get the child's relationship component

			childComponent.parent = parentEntity; //!< Set the child component's parent

			if (parentComponent.children == 0) //!< if the parent has no children
			{
				parentComponent.children = 1; //!< set the number of children to 1
				parentComponent.first = childEntity; //!< set the "first child" to be the child entity
			}
			else //!< Else if the parent entity already has children
			{
				auto currentEntity = parentComponent.first; //!< Get the parent's first child
				for (int i = 1; i < parentComponent.children; i++) //!< Go through the parent's children
				{
					currentEntity = registry.get<RelationshipComponent>(currentEntity).next; //!< Get the next entity each time
				}
				auto& currentComponent = registry.get<RelationshipComponent>(currentEntity).next; //!< Get the relationship component of the final child

				//Temp solution as other way doesnt work
				registry.get<RelationshipComponent>(currentComponent).next = childEntity; //!< set the child entity as the next one after the final child
				//currentComponent.next = childEntity;


				parentComponent.children++; //!< Increase the parent's child number
			}
		}

		void updateChildren()
		{
			entt::registry& registry = Application::getInstance().m_registry; //!< Get the registry

			auto view = registry.view<RelationshipComponent, TransformComponent>(entt::exclude<RootComponent>); //!< Get every entity with a relationship component and Transform component, except if they have a root component.
			for (auto entity : view) //!< Loop through the retrieved entities
			{
				auto& relationship = registry.get<RelationshipComponent>(entity); //!< Get the relationship component
				auto& transform = registry.get<TransformComponent>(entity); //!< Get the transform component

				if (relationship.parent != entt::null) //!< If the entity has a parent
				{
					auto& parentTransform = registry.get<TransformComponent>(relationship.parent); //!< Get the parent's transform
					transform.updateTransform(parentTransform.getTransform()); //!< Update the transform, passing through the parent's transform too.
				}
			}

		}
	}
}