	/* \file UILayer.h */
#pragma once

#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EnTTLayer.h"
#include "UI/widgets.h"
#include "UI/modalWindow.h"
#include "UI/containers.h"
#include "UI/UIComponent.h"

using namespace Engine;

enum class MenuState { Active, Activating, Inactive, Deactivating}; //!< Enum to set the state of the menu. Buttons should only work when active.
class MenuLayer : public Layer
{
public:
	MenuLayer(const char * name); //!< Constructor
	void onRender() override; //!< On render override
	MenuState getState() { return m_state; } //!< getter for the menu state


	virtual void onKeyPressed(KeyPressed & e) override; //!< on mouse moved event override
	virtual void onMouseReleased(MouseReleased & e) override;//!< on mouse released event override
	virtual void onMousePressed(MousePressed & e) override; //!< on mouse pressed event override
	virtual void onMouseMove(MouseMoved & e) override;//!< on mouse move event override

private:
	std::shared_ptr<Free2dOrthographicCamera> m_camera;
	SceneWideUniformsCorrect m_swu; //!< scene wide uniforms
	std::shared_ptr<ResourceManager> rManager; //!< shared pointer to ResourceManager
	ModalWindow m_window; //!< modal window
	
	MenuState m_state = MenuState::Inactive;//!< set the state to be deactive by default


};
