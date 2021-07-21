#pragma once

#include <entt/entt.hpp>


namespace Engine
{
	class RootComponent
	{
	public: //!< Empty component, used just for the name as whatever has this will be the "root".
	};

	class RelationshipComponent
	{
	public:
		std::size_t children = 0; //!< Store the number of children
		entt::entity first = entt::null; //!< Store the first child
		entt::entity next = entt::null; //!< Store the next child
		entt::entity parent = entt::null; //!< Store the parent
	};

	namespace  Hierachy
	{
		void setChild(entt::entity parentEntity, entt::entity childEntity); //!< Setter for the child
		void updateChildren(); //!< Function ot update the children's position
	}
}