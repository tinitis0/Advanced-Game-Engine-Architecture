/* \file containers.h  */
#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "UI/UIComponent.h"
#include "UI/widgets.h"


namespace Engine
{
	class ModalWindow;
	class HorizontalContainer;

	class Container : public UIComponent
	{
	public:
		virtual bool isEmpty() const = 0; //!< Boolean for if container is empty
	};

	class VertContainer : public Container
	{
	public:
		VertContainer() = default; //!< Default constructor
		VertContainer(ModalWindow * parent); //!< Constructor with parent
		virtual void onRender() const override; //!< On render override
		virtual bool isEmpty() const override { return m_containers.empty(); } //!< Checker for if empty
		virtual void addContainer(HorizontalContainer& container); //!< Function to add a horizontal container
		void updatePosition(glm::ivec2& relativePosition) override; //!< Update the position
		void updateSize() override; //!< Update the sizes


		std::vector<HorizontalContainer>::iterator begin() { return m_containers.begin(); } //!< Iterator to call begin each horizontal container
		std::vector<HorizontalContainer>::iterator end() { return m_containers.end(); } //!< Iterator to call end each horiz container
		std::vector<HorizontalContainer>::const_iterator begin() const { return m_containers.begin(); } //!< Const iterator to call begin each horizontal container
		std::vector<HorizontalContainer>::const_iterator end() const { return m_containers.end(); } //!< Const iterator to call begin each horizontal container
	private:
		std::vector<HorizontalContainer> m_containers; //!< List of the containers
	};

	class HorizontalContainer : public Container
	{
	public:
		bool isEmpty() const override { return m_widgets.empty(); } //!< Is empty checker
		template <typename G, typename ...Args> //!< Template for adding a widget

		void addWidget(Args && ... args) //!< Add widget function
		{
			std::shared_ptr<Widget> widget; //!< Make a shared ptr to a widget
			widget.reset(new G(std::forward<Args>(args) ...)); //!< Reset the widget shared ptr to the wisget specified in the args
			widget->setParent(this); //!< set the horizontal container to be the widget's parent
			widget->m_col = m_col; //!< Set the widget's colour
			m_widgets.push_back(widget); //!< Add the widget to the stack
			updateSize(); //!< Update the size
		}
		void updatePosition(glm::ivec2& relativePosition) override; //!< Override to update the position
		void updateSize() override; //!< Update the size override
		void onRender() const override;

		std::vector<std::shared_ptr<Widget>>::iterator begin() { return m_widgets.begin(); }
		std::vector<std::shared_ptr<Widget>>::iterator end() { return m_widgets.end(); }
		std::vector<std::shared_ptr<Widget>>::const_iterator begin() const { return m_widgets.begin(); }
		std::vector<std::shared_ptr<Widget>>::const_iterator end() const { return m_widgets.end(); }
	private:
		std::vector<std::shared_ptr<Widget>> m_widgets; //!< Widget stack
		

	};
}
