/* \file UILayer.h */
#pragma once

#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Engine;

class UILayer : public Layer
{
public:
	UILayer(const char * name);
	void onRender() override;
private:
	std::shared_ptr<Free2dOrthographicCamera> m_camera;
	SceneWideUniformsCorrect m_swu;
	std::vector<Quad> m_quads;

	
};