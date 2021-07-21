/* \file UILayer.h */
#pragma once

#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EnTTLayer.h"

using namespace Engine;

class UILayer : public Layer
{
public:
	UILayer(const char * name); //!< Contructor
	void onRender() override; //!< On render override
	void onUpdate(float timestep) override; //!< Update override, called every frame
private:
	std::shared_ptr<Free2dOrthographicCamera> m_camera; //!< 2D camera
	SceneWideUniformsCorrect m_swu; //!< Scene wide uniforms
	std::vector<Quad> m_quads; //!< stack of quads

	std::shared_ptr<ResourceManager> rManager; //!< Resource manager pointer

	std::shared_ptr<Textures> congratsTex; //!< Congrats texture
};